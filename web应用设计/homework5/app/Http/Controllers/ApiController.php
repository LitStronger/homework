<?php

// namespace App\Http\Controllers;
namespace App\Http\Controllers;

//use App\Http\Requests\RegisterAuthRequest;
use App\User;
use App\ForgotPassword;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Validator;
use JWTAuth;
use Tymon\JWTAuth\Exceptions\JWTException;
use Illuminate\Foundation\Http\FormRequest;
use Illuminate\Support\Facades\Mail;
use Illuminate\Support\Facades\Auth;

class ApiController extends Controller
{

    public function register(Request $request)
    {

        $data_check = Validator::make($request->all(), [
            'name' => 'required|string',
            'email' => 'required|email|unique:users',
            'password' => 'required|string|min:6|max:20'
        ]);
        if(!$data_check->fails()){
            return response()->json([
                'msg' => 'Invalid data, or the email has been registered',
            ], 406);
        }

        $user = new User();
        $user->name = $request->name;
        $user->email = $request->email;
        $user->password = bcrypt($request->password);
        $user->auth_code = \Str::random(24);
        $user->save();

        return response()->json([
            'success' => true,
            'data' => $user
        ], 200);
    }

    public function login(Request $request)
    {
        $input = $request->only('email', 'password');
        $jwt_token = null;

        if (!$jwt_token = JWTAuth::attempt($input)) {
            return response()->json([
                'success' => false,
                'message' => 'Invalid Email or Password',
            ], 401);
        }

        echo "111";

        $users = User::all();
        foreach ($users as $user) {
            echo $user->name;
            echo $user->available;
        }

        if (!$user->available) {
            $this->sendMail($user);
            return response()->json([
                'message' => 'You need active your account first and we have sent you the Verify code. Please login again use verify_token and value with the POST method',
            ], 400);
        }

        return response()->json([
            'success' => true,
            'token' => $jwt_token,
        ]);
    }

    private function sendMail($user)
    {

        echo $user->email;

        Mail::raw('Welcome to webClass2020, and if this is your email please remember the Code "' . $user->auth_code.'"And if you have not known about the website, ignore it.', function ($message) use ($user) {
            $message->to($user->email, $user->name)->subject('Welcome to webClass2020!');
        });
    }

    public function ActiveAccount(Request $request)
    {
        $auth_code_check = Validator::make($request->all(), [
            'auth_code' => 'required',
        ]);
        if ($auth_code_check->fails()) {
            return response()->json(['message' => 'no auth_code',], 400);        
        }

        if(!(User::where(['auth_code' => $request->auth_code])->exists())){
            return response()->json(['message' => 'Invalid auth_code',], 400);        
        }

        User::where(['auth_code' => $request->auth_code])->update(['available' => true]);
        $user = User::find(3);

        return response()->json(['message' => 'Successfully activate!',], 200);        
    }

    public function logout(Request $request)
    {
        $token_check = Validator::make($request->all(), [
            'token' => 'required',
        ]);
        if($token_check->fails()){
            return response()->json(['message'=> 'no token',], 400);
        }

        try {
            JWTAuth::invalidate($request->token);

            return response()->json([
                'success' => true,
                'message' => 'User logged out successfully'
            ]);
        } catch (JWTException $exception) {
            return response()->json([
                'success' => false,
                'message' => 'Sorry, the user cannot be logged out'
            ], 400);
        }
    }

    // public function getAuthUser(Request $request)
    // {
    //     $this->validate($request, [
    //         'token' => 'required'
    //     ]);

    //     $user = JWTAuth::authenticate($request->token);

    //     return response()->json(['user' => $user]);
    // }

    public function forgotPassword(Request $request)
    {

        $email_check = Validator::make($request->all(), [
            'email' => 'required|email|max:40',
        ]);

        if ($email_check->fails()) {
            return response()->json(['message'=> 'Invalid email',], 400);
        }

        $email = $request->email;
        $user = User::where(['email' => $email])->first();
        echo $email;

        if (is_null($user)) {
            return response()->json(['message'=> 'Email not registered',], 404);
        }

        $reset_password_code = \Str::random(24);
        ForgotPassword::updateOrCreate([
            'email' => $email, 
            'reset_password_code' => $reset_password_code,
            'aviliable' => false
        ]);

        Mail::raw('You have forgot your password in WEB class, and if this is your email please remember the Code "' . $reset_password_code.'"And if you have not known about the website, ignore it.', function ($message) use ($user) {
            $message->to($user->email, $user->name)->subject('Reset your password!');
        });

        return response()->json(['Send success , and check your email to receive the Message. ']);
    }

    public function resetPassword(Request $request)
    {


        $data_check = Validator::make($request->all(), [
            'reset_password_code' => 'required',
            'password' => 'required|min:8|max:40',
        ]);
        if ($data_check->fails()) {
            return response()->json(['message'=> 'Invalid data',], 400);
        }

        $reset_password_code = $request->reset_password_code;

        $forgotPassword = new ForgotPassword();
        $forgotPassword = $forgotPassword->where(['reset_password_code' => $reset_password_code])->first();
        if (is_null($forgotPassword) || $forgotPassword->available) {
            return response()->json(['The reset_password_code has been used.',], 403);
        }

        $forgotPassword->available = true;
        $forgotPassword->save();

        $user = new User();
        $user->where(['email' => $forgotPassword->email])->update(['password' => bcrypt($request->password)]);
        return response()->json(['Reset password successfully!',]);
    }


}


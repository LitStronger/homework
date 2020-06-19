<?php

namespace App;

use Illuminate\Foundation\Auth\User as Authenticatable;
use Illuminate\Notifications\Notifiable;
use Tymon\JWTAuth\Contracts\JWTSubject;

/* 注册邮箱验证 */
//use Illuminate\Contracts\Auth\MustVerifyEmail;


class User extends Authenticatable implements JWTSubject//,MustVerifyEmail
{
  //  use Notifiable,\Illuminate\Auth\MustVerifyEmail;


    protected $table = 'users';

    // /**
    //  * The attributes that are mass assignable.
    //  *
    //  * @var array
    //  */
    // protected $fillable = [
    //     'name', 'email', 'password',
    // ];

    // /**
    //  * The attributes that should be hidden for arrays.
    //  *
    //  * @var array
    //  */
    // protected $hidden = [
    //     'password', 'remember_token',
    // ];

    // *
    //  * Get the identifier that will be stored in the subject claim of the JWT.
    //  *
    //  * @return mixed
     
    public function getJWTIdentifier()
    {
        return $this->getKey();
    }

    // /**
    //  * Return a key value array, containing any custom claims to be added to the JWT.
    //  *
    //  * @return array
    //  */
    public function getJWTCustomClaims()
    {
        return [];
    }
    
    public function products()
    {
        return $this->hasMany(Product::class);
    }
}
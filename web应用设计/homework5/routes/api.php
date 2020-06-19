<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| API Routes
|--------------------------------------------------------------------------
|
| Here is where you can register API routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| is assigned the "api" middleware group. Enjoy building your API!
|
*/

Route::post('register', 'ApiController@register');
Route::post('login', 'ApiController@login');
Route::post('active', 'ApiController@ActiveAccount');
Route::post('forgotPassword', 'ApiController@forgotPassword');
Route::post('resetPassword', 'ApiController@resetPassword');



Route::group(['middleware' => 'auth.jwt'], function () {
    Route::get('logout', 'ApiController@logout');
    Route::get('user', 'ApiController@getAuthUser');

	Route::resource('product', 'ProductController');

    // Route::get('showAll', 'ProductController@showAll');
    // Route::get('show/{id}', 'ProductController@show');
    // Route::post('store', 'ProductController@store');
    // Route::put('update/{id}', 'ProductController@update');
    // Route::delete('destroy/{id}', 'ProductController@destroy');
});
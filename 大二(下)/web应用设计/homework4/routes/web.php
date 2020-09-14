<?php

use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/
Auth::routes();

#为Auth\VerificationController这个控制器注册相应路由
Auth::routes(['verify' => true]);

#使用路由中间件限制未验证邮箱用户不能登陆或者访问给定路由
Route::get('/home', 'HomeController@index')->name('home')->middleware('verified');

#使用中间件限制未验证用户访问
Route::get('profile', function(){})->middleware('verified');


Route::get('/welcome', function () {
    return view('welcome');
});
#Auth::routes();
#Route::get('/home', 'HomeController@index')->name('home');
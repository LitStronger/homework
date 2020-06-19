<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class ForgotPassword extends Model
{
    //
    protected $fillable = ['reset_password_code', 'email', 'used'];

}

<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/6
 * Time: 12:22
 */
    $check = $_POST["check"];
    $username = $_COOKIE["username"];
    $pwd = $_POST["pwd"];
    if($check == "check" && $username && pwd){
        setcookie("username","");
        setcookie("pwd","");
    }

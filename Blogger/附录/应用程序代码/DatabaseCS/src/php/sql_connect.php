<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/5
 * Time: 23:03
 */


    $username = $_COOKIE["username"];
    $pwd = $_COOKIE["pwd"];
    $link = mysqli_connect("localhost:3306", $username, $pwd) or die("ERROR");

    if($link -> connect_errno){
        die("sql could not connect: ".mysqli_connect_error());
    }

<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/6
 * Time: 15:15
 */
    $username = $_COOKIE["username"];
    $pwd = $_COOKIE["pwd"];
    include_once ("sql_connect.php");
    //$link = mysqli_connect("localhost:3306",'$username','$pwd');
    /*if($link -> connect_errno){
        die("sql could not connect: ".mysqli_connect_error());
    }*/
    $link->select_db("cyz_blog");
    $age = $_POST["age"];
    $sex = $_POST["sex"];
    $user = $_POST["user"];
    $UpdateSql = <<<Updatesql
        Update cyz_user set age = $age, sex = '$sex' Where name = '$user';
Updatesql;
    // $link->set_charset('gb2312');
    $res = mysqli_query($link, $UpdateSql);
    echo "Yes";
    mysqli_close($link);
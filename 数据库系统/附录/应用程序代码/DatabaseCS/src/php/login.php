<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/5
 * Time: 20:53
 */
    date_default_timezone_set("PRC");
    header("Content-Type:text/html;charset=utf-8");
    @session_start();
    $username = $_POST["username"];
    $pwd = $_POST["pwd"];
    $link = mysqli_connect("localhost:3306",$username,$pwd) or die("ERROR");

    if($link){
        setcookie('username',$username,time()+100000);
        setcookie('pwd',$pwd, time() + 100000);
        echo "Yes";
    }
    mysqli_close($link);

    /*
    $loginSql = <<<login
        select * from cyz_user where name = "{$username}";
login;

    $res = mysqli_query($link, $loginSql);
    $row = $res->fetch_row();
    if($row){
        $_SESSION["username"] = $row;
        setcookie('username',$username,time()+100000);
        setcookie('pwd',$pwd, time() + 100000);
        echo "Yes";

    }else{
        echo "登录失败";
    }
    */



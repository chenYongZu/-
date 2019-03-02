<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/5
 * Time: 20:58
 */

    date_default_timezone_set("PRC");
    header("Content-Type:text/html;charset=utf-8");
    $link = mysqli_connect("localhost:3306", "cyz_bloger", "123456") or die("ERROR");

    $link->select_db("cyz_blog");

    $username = $_POST["username"];
    $pwd = $_POST["pwd"];
    $age = $_POST["age"];
    $sex = $_POST["sex"];
    $email = $_POST["email"];
    $rank = 0;
    $date = date("Y-m-d");

    $insertUserSql = <<<insertUserSql
    Insert Into cyz_user
    values ('$username','$email', '$sex', $age, $rank, '$date');
insertUserSql;

    $isOk = mysqli_query($link, $insertUserSql);
    if($isOk){
        echo "Yes";
    }else{
        echo "No";
    }
    mysqli_close($link);
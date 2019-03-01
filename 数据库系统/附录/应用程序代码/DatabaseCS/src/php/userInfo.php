<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/6
 * Time: 12:07
 */
    $username = $_COOKIE["username"];
    $pwd = $_COOKIE["pwd"];
    include_once ("sql_connect.php");
    //$link = mysqli_connect("localhost:3306",'$username','$pwd');
    /*if($link -> connect_errno){
        die("sql could not connect: ".mysqli_connect_error());
    }*/
    $link->select_db("cyz_blog");
    $loginSql = <<<login
            select * from cyz_user where name = "{$username}";
login;
   // $link->set_charset('gb2312');
    $res = mysqli_query($link, $loginSql);

    while ($row = $res->fetch_row()) {
        foreach ($row as $i) {
            echo $i . "<br>";
        }
    }
    mysqli_close($link);
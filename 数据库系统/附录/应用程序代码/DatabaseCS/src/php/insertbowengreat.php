<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/7
 * Time: 1:26
 */

    date_default_timezone_set("PRC");
    header("Content-Type:text/html;charset=utf-8");
    $username = $_COOKIE["username"];
    $pwd = $_COOKIE["pwd"];
    include_once ("sql_connect.php");
    //$link = mysqli_connect("localhost:3306",'$username','$pwd');
    /*if($link -> connect_errno){
        die("sql could not connect: ".mysqli_connect_error());
    }*/
    $link->select_db("cyz_blog");
    $blog_id = $_POST["blog_id"];

    $Insertbowengreat =<<< Insertbowengreat
              Update cyz_bowen set great = great + 1 Where blog_id = '$blog_id';
Insertbowengreat;

    // $link->set_charset('gb2312');
    $res = mysqli_query($link, $Insertbowengreat);
    echo "Yes";

    mysqli_close($link);
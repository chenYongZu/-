<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/6
 * Time: 22:57
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
    $searchtitle = $_POST["searchtitle"];



    $Insertbowencomment_num =<<< Insertbowencomment_num
          Update cyz_bowen set visit = visit + 1 Where title = '$searchtitle';
Insertbowencomment_num;

    // $link->set_charset('gb2312');
    $res = mysqli_query($link, $Insertbowencomment_num);

    $SearchBowen =<<< SearchBowen
            Select * From cyz_bowen_view Where blog_title = "$searchtitle";
SearchBowen;


    // $link->set_charset('gb2312');
    $res = mysqli_query($link, $SearchBowen);
    while ($row = $res->fetch_row()) {
        foreach ($row as $i) {
            echo $i . "<br>";
        }
    }

    mysqli_close($link);
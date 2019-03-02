<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/7
 * Time: 11:03
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
    $title = $_POST["title"];

    $SearchComment =<<< SearchComment
          Select * From cyz_comment_view Where blog_title = "$title";
SearchComment;

    // $link->set_charset('gb2312');
    $res = mysqli_query($link, $SearchComment);
    while ($row = $res->fetch_row()) {
        foreach ($row as $i) {
            echo $i . "<br>";
        }
        echo "<pr>";
    }

    mysqli_close($link);
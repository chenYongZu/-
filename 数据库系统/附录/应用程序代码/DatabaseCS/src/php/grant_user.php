<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/8
 * Time: 14:30
 */
/*
    $username = $_POST["username"];
    $pwd = $_POST["pwd"];*/
    if($username){
        $fp = fopen("../other/grant.txt","w") or die("Unable to open file!");
        $txt = "use cyz_blog;\n";
        fwrite($fp, $txt);

        $tmp = $username.""."'@localhost Identified by '"."".$pwd.""."';\n";
        $one = "Grant Select, Update on cyz_user to '"."".$tmp;
        fwrite($fp,$one);  // cyz_user

        $one = "Grant Select on cyz_label to '"."".$tmp;
        fwrite($fp,$one);  //cyz_label

        $one = "Grant Select, Update, Insert on cyz_bowen to '"."".$tmp;
        fwrite($fp,$one);  //cyz_bowen

        $one = "Grant Select, Insert on cyz_ub to '"."".$tmp;
        fwrite($fp,$one);  //cyz_ub

        $one = "Grant Insert on cyz_comment to '"."".$tmp;
        fwrite($fp,$one);  //cyz_comment

        $one = "Grant Select on cyz_user_view to '"."".$tmp;
        fwrite($fp,$one);  //cyz_uer_view

        $one = "Grant Select on cyz_bowen_view to '"."".$tmp;
        fwrite($fp,$one);  //cyz_bowen_view

        $one = "Grant Select on cyz_comment_view to '"."".$tmp;
        fwrite($fp,$one);  //cyz_comment_view

        fwrite($fp,"exit;");

        fclose($fp);

        $grant_path = "D://phpStudy//PHPTutorial//WWW//DatabaseCS//src//other//grant_user.bat";
        exec($grant_path);
    }
    /*
    $username = "cyz_bloger";
    $pwd = "123456";
    $tmp = $username.""."'@localhost Identified by '"."".$pwd.""."';\n";
    $fp = fopen("../other/grant.txt","w") or die("Unable to open file!");

    $one = "Grant Select, Update on cyz_user to '"."".$tmp;
    fwrite($fp,$one);  // cyz_user

    $one = "Grant Select on cyz_label to '"."".$tmp;
    fwrite($fp,$one);  //cyz_label

    $one = "Grant Select, Update, Insert on cyz_bowen to '"."".$tmp;
    fwrite($fp,$one);  //cyz_bowen

    $one = "Grant Select, Insert on cyz_ub to '"."".$tmp;
    fwrite($fp,$one);  //cyz_ub

    $one = "Grant Insert on cyz_comment to '"."".$tmp;
    fwrite($fp,$one);  //cyz_comment

    $one = "Grant Select on cyz_user_view to '"."".$tmp;
    fwrite($fp,$one);  //cyz_uer_view

    $one = "Grant Select on cyz_bowen_view to '"."".$tmp;
    fwrite($fp,$one);  //cyz_bowen_view

    $one = "Grant Select on cyz_comment_view to to '"."".$tmp;
    fwrite($fp,$one);  //cyz_comment_view

    fclose($fp);
    */
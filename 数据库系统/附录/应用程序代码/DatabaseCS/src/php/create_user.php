<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/8
 * Time: 11:57
 */
    $username = $_POST["username"];
    $pwd = $_POST["pwd"];

    $fp = fopen("../other/user.txt","w") or die("Unable to open file!");
    $txt = "use mysql;\n";
    fwrite($fp, $txt);
    fwrite($fp, "Create user '");
    fwrite($fp, $username);
    fwrite($fp, "'@'localhost' Identified by '");
    fwrite($fp, $pwd);
    fwrite($fp, "';\n");
    fwrite($fp, "exit;");
    fclose($fp);

    $create_path = "D://phpStudy//PHPTutorial//WWW//DatabaseCS//src//other//create_user.bat";
    exec($create_path);
    include_once("grant_user.php");
<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/8
 * Time: 2:06
 */

    include_once ("sql_connect.php");
    //$link = mysqli_connect("localhost:3306",'$username','$pwd');
    /*if($link -> connect_errno){
        die("sql could not connect: ".mysqli_connect_error());
    }*/
    $user = $_POST["user"];
    $link->select_db("cyz_blog");
    $searchSql = <<<searchSql
          select * from cyz_user_view where user_name = "{$user}";
searchSql;
    // $link->set_charset('gb2312');
    $res = mysqli_query($link, $searchSql);

    while ($row = $res->fetch_row()) {
        foreach ($row as $i) {
            echo $i . "<br>";
        }
    }
    mysqli_close($link);
<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/8
 * Time: 17:33
 */

    date_default_timezone_set("PRC");
    header("Content-Type:text/html;charset=utf-8");

    include_once ("sql_connect.php");

    $link->select_db("cyz_blog");
    $label_id = $_POST["label_id"];

    $SearchLabel =<<< SearchLabel
          Select * From cyz_label Where label_id = "$label_id";
SearchLabel;

    // $link->set_charset('gb2312');
    $res = mysqli_query($link, $SearchLabel);
    $row = $res->fetch_row()[1];
    echo $row;

    mysqli_close($link);
<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/6
 * Time: 19:52
 */
    date_default_timezone_set("PRC");
    header("Content-Type:text/html;charset=utf-8");
    include_once ("sql_connect.php");

    $link->select_db("cyz_blog");
    $title = $_POST["title"];
    $blog_content = $_POST["blog_content"];
    $label_id = $_POST["label_id"];
    $publish_date = date("Y-m-d");

    $InsertBowen =<<< InsertBowen
      Insert Into cyz_bowen(title, visit, great, comment_num, content, publish_date) 
      Values('$title', 0, 0, 0, '$blog_content','$publish_date');
InsertBowen;

    $res = mysqli_query($link, $InsertBowen);

    $searchUserSql = <<<searchUserSql
    select * from cyz_bowen where title = "{$title}"
searchUserSql;
    $res = mysqli_query($link, $searchUserSql);
    $row = $res->fetch_row()[0];

    $Insertub =<<< Insertub
      Insert Into cyz_ub(blog_id, name, label_id, assort_id) 
      Values($row, '$username', $label_id, 0);
Insertub;
    $res = mysqli_query($link, $Insertub);
    echo "Yes";

    mysqli_close($link);
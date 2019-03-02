<?php
/**
 * Created by PhpStorm.
 * User: Y_Z
 * Date: 2019/1/7
 * Time: 1:06
 */

    date_default_timezone_set("PRC");
    header("Content-Type:text/html;charset=utf-8");
    include_once ("sql_connect.php");

    $link->select_db("cyz_blog");
    $content = $_POST["content"];
    $blog_id = $_POST["blog_id"];

    $InsertComment =<<< InsertComment
          Insert Into cyz_comment(blog_id, name, comment_date, content) 
          Values($blog_id, '$username', CURRENT_TIMESTAMP() , '$content');
InsertComment;

    // $link->set_charset('gb2312');
    $res = mysqli_query($link, $InsertComment);

    $InsertComment_sum =<<< InsertComment_sum
        Update cyz_bowen set comment_num = comment_num + 1 Where blog_id = '$blog_id';
InsertComment_sum;

    $res = mysqli_query($link,$InsertComment_sum);

    echo "Yes";

    mysqli_close($link);
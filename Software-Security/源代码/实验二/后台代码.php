<?php
    header('Content-type:text/html;charset:utf-8');
    $link = mysqli_connect("localhost:3306","cyz_user2","123456");
    if($link -> connect_errno){
        die("sql could not connect: ".mysqli_connect_error());
    }
    else {
        echo "SUCCESS TO SELECT" . "<br>";
        $id = $_POST['id'];
        $link->select_db("student");
        $link->set_charset('gb2312');
        $res = $link->query("Select * From cyz_student where cyz_Sno = $id");

        while ($row = $res->fetch_row()) {
            foreach ($row as $i) {
                echo $i . " ";
            }
            echo "<br>";
        }
    }

    mysqli_close($link);
>


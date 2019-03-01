/**建立数据库和基本表*/
Create Database cyz_Blog;
Create Table cyz_user
(
	name CHAR(15) PRIMARY KEY COMMENT '账号',
	email CHAR(20) UNIQUE COMMENT '邮箱',
	sex enum('男','女') NOT NULL,
	age SMALLINT,
	rank INT COMMENT '等级',
	reg_time DATE COMMENT '注册日期'
);

Create Table cyz_bowen
(
	blog_id BIGINT(20) NOT NULL AUTO_INCREMENT PRIMARY KEY,
	title CHAR(50) ,
	visit INT COMMENT '浏览量',
	great INT COMMENT '点赞数',
	comment_num INT COMMENT '评论数目',
	content TEXT COMMENT '评论内容',
	publish_date DATE
);

Create Table cyz_label
(
	label_id BIGINT(20) NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name CHAR(15) UNIQUE COMMENT'标签名称',
	descri text COMMENT '标签描述'
);


Create Table cyz_assort
(
	assort_id BIGINT(20) NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name CHAR(15) UNIQUE COMMENT '分类名称',
	father_id BIGINT(20) COMMENT '父分类ID',
	descri text COMMENT '分类描述'
);

Create Table cyz_comment
(
	blog_id BIGINT(20) NOT NULL,
	name CHAR(15) NOT NULL,
	comment_date DATE,
	great INT,
	content TEXT COMMENT '内容',
	PRIMARY KEY(blog_id, name, comment_date),
	FOREIGN KEY(blog_id) REFERENCES cyz_bowen(blog_id)
	on Delete Cascade on Update Cascade,
 	FOREIGN KEY(name) REFERENCES cyz_user(name)
 	on Delete Cascade on Update Cascade
);


Create Table cyz_ub
(
	blog_id BIGINT(20) NOT NULL,
	name CHAR(15) COMMENT '用户账号昵称',
	label_id BIGINT(20),
	assort_id BIGINT(20),
	PRIMARY KEY(blog_id, name),
	FOREIGN KEY(blog_id) REFERENCES cyz_bowen(blog_id)
	on Delete Cascade on Update Cascade,
 	FOREIGN KEY(name) REFERENCES cyz_user(name)
 	on Delete Cascade on Update Cascade
);

/**建立视图*/
Create View cyz_user_view(user_name, user_sex, user_age, user_rank)
As Select name, sex, age, rank From cyz_user;

Create View cyz_bowen_view
(user_name, blog_title, blog_id, label_id, assort_id, content, great, visit, publish_date, comment_num)
As Select name, title, cyz_bowen.blog_id, label_id, assort_id, content, great, visit, publish_date, comment_num
From cyz_ub, cyz_bowen Where cyz_ub.blog_id = cyz_bowen.blog_id;

Create View cyz_comment_view
(blog_title, comment_user_name, comment_date, content)
As Select title, name, comment_date, cyz_comment.content 
From cyz_bowen, cyz_comment Where cyz_bowen.blog_id = cyz_comment.blog_id;


/**建立索引*/
Alter View cyz_bowen_view Add Index cyz_blogtitle_index(blog_title);
Alter Table cyz_bowen Add Index cyz_blogtitle_index(title);


/**创建管理员用户*/
Create User cyz_bloger@localhost Identified By '123456';

Grant All Privileges On cyz_Blog.* To cyz_bloger@localhost with grant option;
Grant All Privileges On mysql.* To cyz_bloger@localhost with grant option;

/**创建两个普通用户并授权*/
Create User cyz_user1@localhost Identified By '123456';
Create User cyz_user2@localhost Identified By '123456';

Grant Select, Update on cyz_user to 'cyz_user1'@localhost Identified by '123456';
Grant Select on cyz_label to 'cyz_user1'@localhost Identified by '123456';
Grant Select, Update, Insert on cyz_bowen to 'cyz_user1'@localhost Identified by '123456';
Grant Select, Insert on cyz_ub to 'cyz_user1'@localhost Identified by '123456';
Grant Insert on cyz_comment to 'cyz_user1'@localhost Identified by '123456';
Grant Select on cyz_user_view to 'cyz_user1'@localhost Identified by '123456';
Grant Select on cyz_bowen_view to 'cyz_user1'@localhost Identified by '123456';
Grant Select on cyz_comment_view to 'cyz_user1'@localhost Identified by '123456';


Grant Select, Update on cyz_user to 'cyz_user2'@localhost Identified by '123456';
Grant Select on cyz_label to 'cyz_user2'@localhost Identified by '123456';
Grant Select, Update, Insert on cyz_bowen to 'cyz_user2'@localhost Identified by '123456';
Grant Select, Insert on cyz_ub to 'cyz_user2'@localhost Identified by '123456';
Grant Insert on cyz_comment to 'cyz_user2'@localhost Identified by '123456';
Grant Select on cyz_user_view to 'cyz_user2'@localhost Identified by '123456';
Grant Select on cyz_bowen_view to 'cyz_user2'@localhost Identified by '123456';
Grant Select on cyz_comment_view to 'cyz_user2'@localhost Identified by '123456';

/**插入几个标签*/
Insert Into cyz_label(name, descri) Values ('科技',"描述科技类的博文");
Insert Into cyz_label(name, descri) Values ('情感',"描述情感类的博文");
Insert Into cyz_label(name, descri) Values ('体育',"描述体育类的博文");
Insert Into cyz_label(name, descri) Values ('电影',"描述电影类的博文");

Insert Into cyz_user Value("cyz_user1","cyz_user1@qq.com",'男',12,0,"1999-09-11");
Insert Into cyz_user Value("cyz_user2","cyz_user2@qq.com",'女',18,0,"2005-09-16");


/**插入博文信息*/
Insert Into cyz_bowen(title, visit, great, comment_num, content, publish_date)
Values("数据库课程",0,0,0, "一门好课程应该这样学习。。。。。。","2019-01-01");

Insert Into cyz_bowen(title, visit, great, comment_num, content, publish_date)
Values("物理课程",0,0,0, "一门好课程应该这样学习。。。。。。","2019-01-01");

Insert Into cyz_bowen(title, visit, great, comment_num, content, publish_date)
Values("数学课程",0,0,0, "一门好课程应该这样学习。。。。。。","2019-01-01");

Insert Into cyz_bowen(title, visit, great, comment_num, content, publish_date)
Values("英语课程",0,0,0, "一门好课程应该这样学习。。。。。。","2019-01-01");

/**插入用户-博文信息*/
Insert Into cyz_ub(blog_id, name, label_id, assort_id)
Values(24, 'cyz_user1', 1, 0);

Insert Into cyz_ub(blog_id, name, label_id, assort_id)
Values(25, 'cyz_user2', 1, 0);

Insert Into cyz_ub(blog_id, name, label_id, assort_id)
Values(26, 'cyz_user1', 1, 0);

Insert Into cyz_ub(blog_id, name, label_id, assort_id)
Values(27, 'cyz_user2', 2, 0);

/**插入评论信息*/
Insert Into cyz_comment(blog_id, name, comment_date, content)
Values(24, 'cyz_user1', '2019-1-2 10:12:23', "说的没错！");

Insert Into cyz_comment(blog_id, name, comment_date, content)
Values(25, 'cyz_user1', '2019-1-2 10:12:21', "我觉得可以！");

Insert Into cyz_comment(blog_id, name, comment_date, content)
Values(26, 'cyz_user1', '2019-1-2 10:12:22', "还行！");

Insert Into cyz_comment(blog_id, name, comment_date, content)
Values(24, 'cyz_user2', '2019-1-2 10:12:23', "妙啊！");

/**备份数据代码*/
mysqldump -u root -p cyz_blog > D:/cyz_blog_backup.sql

/**恢复数据代码*/
mysql -u root -p < D:/cyz_blog_backup.sql


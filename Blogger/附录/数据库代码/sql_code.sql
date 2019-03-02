/**�������ݿ�ͻ�����*/
Create Database cyz_Blog;
Create Table cyz_user
(
	name CHAR(15) PRIMARY KEY COMMENT '�˺�',
	email CHAR(20) UNIQUE COMMENT '����',
	sex enum('��','Ů') NOT NULL,
	age SMALLINT,
	rank INT COMMENT '�ȼ�',
	reg_time DATE COMMENT 'ע������'
);

Create Table cyz_bowen
(
	blog_id BIGINT(20) NOT NULL AUTO_INCREMENT PRIMARY KEY,
	title CHAR(50) ,
	visit INT COMMENT '�����',
	great INT COMMENT '������',
	comment_num INT COMMENT '������Ŀ',
	content TEXT COMMENT '��������',
	publish_date DATE
);

Create Table cyz_label
(
	label_id BIGINT(20) NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name CHAR(15) UNIQUE COMMENT'��ǩ����',
	descri text COMMENT '��ǩ����'
);


Create Table cyz_assort
(
	assort_id BIGINT(20) NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name CHAR(15) UNIQUE COMMENT '��������',
	father_id BIGINT(20) COMMENT '������ID',
	descri text COMMENT '��������'
);

Create Table cyz_comment
(
	blog_id BIGINT(20) NOT NULL,
	name CHAR(15) NOT NULL,
	comment_date DATE,
	great INT,
	content TEXT COMMENT '����',
	PRIMARY KEY(blog_id, name, comment_date),
	FOREIGN KEY(blog_id) REFERENCES cyz_bowen(blog_id)
	on Delete Cascade on Update Cascade,
 	FOREIGN KEY(name) REFERENCES cyz_user(name)
 	on Delete Cascade on Update Cascade
);


Create Table cyz_ub
(
	blog_id BIGINT(20) NOT NULL,
	name CHAR(15) COMMENT '�û��˺��ǳ�',
	label_id BIGINT(20),
	assort_id BIGINT(20),
	PRIMARY KEY(blog_id, name),
	FOREIGN KEY(blog_id) REFERENCES cyz_bowen(blog_id)
	on Delete Cascade on Update Cascade,
 	FOREIGN KEY(name) REFERENCES cyz_user(name)
 	on Delete Cascade on Update Cascade
);

/**������ͼ*/
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


/**��������*/
Alter View cyz_bowen_view Add Index cyz_blogtitle_index(blog_title);
Alter Table cyz_bowen Add Index cyz_blogtitle_index(title);


/**��������Ա�û�*/
Create User cyz_bloger@localhost Identified By '123456';

Grant All Privileges On cyz_Blog.* To cyz_bloger@localhost with grant option;
Grant All Privileges On mysql.* To cyz_bloger@localhost with grant option;

/**����������ͨ�û�����Ȩ*/
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

/**���뼸����ǩ*/
Insert Into cyz_label(name, descri) Values ('�Ƽ�',"�����Ƽ���Ĳ���");
Insert Into cyz_label(name, descri) Values ('���',"���������Ĳ���");
Insert Into cyz_label(name, descri) Values ('����',"����������Ĳ���");
Insert Into cyz_label(name, descri) Values ('��Ӱ',"������Ӱ��Ĳ���");

Insert Into cyz_user Value("cyz_user1","cyz_user1@qq.com",'��',12,0,"1999-09-11");
Insert Into cyz_user Value("cyz_user2","cyz_user2@qq.com",'Ů',18,0,"2005-09-16");


/**���벩����Ϣ*/
Insert Into cyz_bowen(title, visit, great, comment_num, content, publish_date)
Values("���ݿ�γ�",0,0,0, "һ�źÿγ�Ӧ������ѧϰ������������","2019-01-01");

Insert Into cyz_bowen(title, visit, great, comment_num, content, publish_date)
Values("����γ�",0,0,0, "һ�źÿγ�Ӧ������ѧϰ������������","2019-01-01");

Insert Into cyz_bowen(title, visit, great, comment_num, content, publish_date)
Values("��ѧ�γ�",0,0,0, "һ�źÿγ�Ӧ������ѧϰ������������","2019-01-01");

Insert Into cyz_bowen(title, visit, great, comment_num, content, publish_date)
Values("Ӣ��γ�",0,0,0, "һ�źÿγ�Ӧ������ѧϰ������������","2019-01-01");

/**�����û�-������Ϣ*/
Insert Into cyz_ub(blog_id, name, label_id, assort_id)
Values(24, 'cyz_user1', 1, 0);

Insert Into cyz_ub(blog_id, name, label_id, assort_id)
Values(25, 'cyz_user2', 1, 0);

Insert Into cyz_ub(blog_id, name, label_id, assort_id)
Values(26, 'cyz_user1', 1, 0);

Insert Into cyz_ub(blog_id, name, label_id, assort_id)
Values(27, 'cyz_user2', 2, 0);

/**����������Ϣ*/
Insert Into cyz_comment(blog_id, name, comment_date, content)
Values(24, 'cyz_user1', '2019-1-2 10:12:23', "˵��û��");

Insert Into cyz_comment(blog_id, name, comment_date, content)
Values(25, 'cyz_user1', '2019-1-2 10:12:21', "�Ҿ��ÿ��ԣ�");

Insert Into cyz_comment(blog_id, name, comment_date, content)
Values(26, 'cyz_user1', '2019-1-2 10:12:22', "���У�");

Insert Into cyz_comment(blog_id, name, comment_date, content)
Values(24, 'cyz_user2', '2019-1-2 10:12:23', "���");

/**�������ݴ���*/
mysqldump -u root -p cyz_blog > D:/cyz_blog_backup.sql

/**�ָ����ݴ���*/
mysql -u root -p < D:/cyz_blog_backup.sql


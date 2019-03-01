#include<stdio.h>
#include<stdlib.h>

#define TRUE 1  //判断树是否增高了或者降低了
#define FALSE 0 //表示树的高度没有改变
#define LH +1 //左边高
#define EH 0  //左右一样高
#define RH -1 //右边高
#define N 10  //N是限定平衡二叉树的棵树
typedef int Status;
typedef int ElemType; // 这里采用int类型进行操作

/*链式存储结构*/
typedef struct BBSTNode{
    ElemType data;   //数据域
    int bf;          //平衡因子
    struct BBSTNode *lchild ,*rchild; //左右孩子指针
} BBSTNode,*BBSTree;

Status SearchBBSTree(BBSTree T,ElemType e);//查找节点存在性

void R_Rotate(BBSTree &p);//右旋

void L_Rotate(BBSTree &p);//左旋

void LeftBalance(BBSTree &T);//插入左平衡调整

void RightBalance(BBSTree &T);//插入右平衡调整

Status InsertAVL(BBSTree &T,ElemType e,int &taller);//插入节点

void DELeftBalance(BBSTree &T);//删除左平衡调整

void DERightBalance(BBSTree &T);//删除右平衡调整

Status Delete(BBSTree &T,int &shorter);//删除操作

void SDelete(BBSTree &T,BBSTree &q,BBSTree &s,int &shorter);//查找后继节点操作

Status DeleteAVL(BBSTree &T,ElemType e,int &shorter);//删除节点操作

void MergeBBSTree(BBSTree &T1,BBSTree &T2);//合并两棵树

void SplitBBSTree(BBSTree T,ElemType e,BBSTree &T1,BBSTree &T2);//分裂两棵树

void Split(BBSTree T,ElemType e,BBSTree &T1,BBSTree &T2); //递归分裂操作

void PrintBBSTree(BBSTree &T,int dep); //凹入表显示

void DestroyBBSTree(BBSTree &T);// 销毁平衡二叉树

/*右旋操作*/
void R_Rotate(BBSTree &p){
    BBSTree lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}

/*左旋操作*/
void L_Rotate(BBSTree &p){
    BBSTree rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}
/*插入左平衡调整*/
void LeftBalance(BBSTree &T){
    BBSTree lc,rd;
    lc=T->lchild;
    switch(lc->bf){
        case LH: T->bf = lc->bf=EH;R_Rotate(T);break; //LL型，一次右旋
        case RH:                                      //LR型，一次左旋，一次右旋
            rd=lc->rchild;
            switch(rd->bf){
                /*修改原来平衡因子，并判断是否需要调整*/
                case LH:T->bf=RH;lc->bf=EH;break;
                case EH:T->bf=lc->bf=EH;break;
                case RH:T->bf=EH;lc->bf=LH;break;
        }
        rd->bf=EH;
        L_Rotate(T->lchild);
        R_Rotate(T);
        break;
    }
}
/*插入右平衡调整*/
void RightBalance(BBSTree &T){
    BBSTree rc,ld;
    rc=T->rchild;
    switch(rc->bf){
        case RH:T->bf= rc->bf=EH;L_Rotate(T);break;  //RR型，一次左旋
        case LH:                                     //RL型，一次右旋，一次左旋
            ld=rc->lchild;
            switch(ld->bf){
                case LH:T->bf=RH;rc->bf=EH;break;
                case EH:T->bf=rc->bf=EH;break;
                case RH:T->bf = EH;rc->bf=LH;break;
        }
        ld->bf=EH;
        R_Rotate(T->rchild);    //以T的有孩子为轴右旋
        L_Rotate(T);            //左旋
        break;
    }
}
/*插入节点*/
Status InsertAVL(BBSTree &T,ElemType e,int &taller)
{
    if(T==NULL){ /*空树，新建节点*/
        T= (BBSTree) malloc (sizeof(BBSTNode));
        T->data = e;
        T->lchild = T->rchild = NULL;
        T->bf = EH;
        taller = TRUE;   //高度增加1
    }
    else{   /*非空树*/
        if(e == T->data){ /*已经存在该节点，不进行插入操作*/
            taller = FALSE;
            return FALSE;
        }
        else if(e < T->data){ /*插入节点小于当前节点，对左子树递归找插入位置*/
            if(!InsertAVL(T->lchild,e,taller)) return FALSE; // 找不到，插入失败
            if(taller) /*对插入后高度变化进行调整*/
                switch(T->bf){
                    /*分情况讨论高度变化取值的影响*/
                    case LH:LeftBalance(T);taller = FALSE;break; //左高了，左平衡调整
                    case EH:T->bf = LH;taller = TRUE;break;
                    case RH:T->bf = EH;taller = FALSE;break;
                }
        }
        else{ /*插入节点大于当前节点，对右子树递归找插入位置*/
            if (!InsertAVL(T->rchild,e,taller)) return FALSE;
            if(taller) /*对插入节点后高度变化进行分情况讨论*/
                switch(T->bf){
                    case LH:T->bf = EH;taller = FALSE;break;
                    case EH:T->bf = RH;taller = TRUE;break;
                    case RH:RightBalance(T);taller = FALSE;break; //右边高了，右平衡调整
                }
        }
    }
    return TRUE;
}
/*删除左平衡调整*/
void DELeftBalance(BBSTree &T){
    BBSTree lc,rd;
    lc=T->lchild;
    switch(lc->bf){ /*对删除节点左子树进行判断是否需要调整*/
        case LH:T->bf = EH;R_Rotate(T);break;
        case EH:T->bf = lc->bf= EH;R_Rotate(T);break; //右旋处理
        case RH:
        rd=lc->rchild;
        switch(rd->bf){ /*失衡，修改当前节点及其子树bf值，并进行后续调整*/
            case LH:T->bf=RH;lc->bf=EH;break;
            case EH:T->bf=lc->bf=EH;break;
            case RH:T->bf=EH;lc->bf=LH;break;
        }
        rd->bf=EH;
        L_Rotate(T->lchild);  //删除操作的LR型调整
        R_Rotate(T);
    }
}
/*删除右平衡调整*/
void DERightBalance(BBSTree &T){
    BBSTree rc,ld;
    rc=T->rchild;
    switch(rc->bf){/*操作机理与左平衡操作相反，思想类似*/
        case RH:T->bf= EH;L_Rotate(T);break;
        case EH:T->bf= EH; L_Rotate(T);break;
        case LH:
            ld=rc->lchild;
            switch(ld->bf){
                case LH:T->bf=RH;rc->bf=EH;break;
                case EH:T->bf=rc->bf=EH;break;
                case RH:T->bf = EH;rc->bf=LH;break;
        }
        ld->bf=EH;
        R_Rotate(T->rchild);
        L_Rotate(T);
    }
}
/*寻找后继节点并代替删除节点位置*/
void SDelete(BBSTree &T,BBSTree &q,BBSTree &s,int &shorter){
    if(s->rchild){/*删除节点右子树非空，递归寻找适合的后继节点*/
        SDelete(T,s,s->rchild,shorter);//递归
        if(shorter) /*判断树的高度是否变矮了*/
            switch(s->bf){
                case EH:s->bf = LH;shorter = FALSE;break;
                case RH:s->bf = EH;shorter = TRUE;break;
                case LH:DELeftBalance(s);shorter = FALSE;break;
            }
        return;
    }
    /*当前删除节点位置的数值修改为后继节点的数值*/
    T->data = s->data;
    if(q != T) q->rchild = s->lchild;
    else q->lchild = s->lchild;
    shorter = TRUE;
}
/*删除节点*/
Status Delete(BBSTree &T,int &shorter){
    BBSTree q;
    if(T->rchild==NULL){ /*右子树为空，直接删除当前删除节点，接上左子树，修改高度*/
        q = T;
        T = T->lchild;
        free(q); //释放节点空间
        shorter = TRUE;
    }
    else if(T->lchild==NULL){ /*若左子树为空，操作与右子树类似*/
        q = T;
        T= T->rchild;
        free(q);
        shorter = TRUE;
    }
    else{  /*若左右子树都非空*/
        SDelete(T,T,T->lchild,shorter);//递归查找后继节点替代
        if(shorter) /*找到后继节点并修改后，回溯判断高度变化，做适当平衡调整*/
            switch(T->bf){
                case EH:T->bf = RH;shorter = FALSE;break;
                case LH:T->bf = EH;shorter = TRUE;break;
                case RH:DERightBalance(T);shorter = FALSE;break;
            }
    }
    return TRUE;
}
/*查找要删除的节点，删除节点*/
Status DeleteAVL(BBSTree &T,ElemType e,int &shorter){
    int sign = FALSE;
    if (T==NULL) return sign; //树为空树，删除失败
    else{ //找到要删除的节点，调用Delete做删除操作
        if(e == T->data){
            sign = Delete(T,shorter);
            return sign;
        }
        else if(e < T->data){ //删除节点值小于当前节点值
            sign = DeleteAVL(T->lchild,e,shorter);//左递归查找删除节点是否存在
            if(shorter)/*调整平衡*/
                switch(T->bf){
                    case EH:T->bf = RH;shorter = FALSE;break;
                    case LH:T->bf = EH;shorter = TRUE;break;
                    case RH:DERightBalance(T);shorter = TRUE;break;
                }
            return sign;
        }
        else{ /*对右子树操作，类似于以上对左子树操作*/
            sign = DeleteAVL(T->rchild,e,shorter);
            if(shorter)
                switch(T->bf){
                    case EH:T->bf = LH;shorter = FALSE;break;
                    case RH:T->bf = EH;break;
                    case LH:DELeftBalance(T);shorter = FALSE;
                    break;
                }
            return sign;
        }
    }
}
/*合并两棵平衡二叉树*/
void MergeBBSTree(BBSTree &T1,BBSTree &T2){
    int taller = FALSE;
    if(T2==NULL) return;  //一棵树为空，直接返回结束
    MergeBBSTree(T1,T2->lchild); //遍历查找T2左子树节点
    InsertAVL(T1,T2->data,taller); //对遍历出来的节点分别插入T1上
    MergeBBSTree(T1,T2->rchild);//遍历查找T2右子树节点
}
/*递归分裂操作*/
void Split(BBSTree T,ElemType e,BBSTree &T1,BBSTree &T2){
    int taller = FALSE;
    if(T==NULL) return; //若是空树，直接返回
    Split(T->lchild,e,T1,T2);//对左子树查找e，分裂左子树（原因e的左子树都小于e）
    if(T->data > e) InsertAVL(T2,T->data,taller); //对分裂出来的节点（>e）插入到T2
    else InsertAVL(T1,T->data,taller); //（<e）插入到T1
    Split(T->rchild,e,T1,T2);//查找右子树
}
/*一棵平衡二叉树分裂为两棵平衡二叉树*/
void SplitBBSTree(BBSTree T,ElemType e,BBSTree &T1,BBSTree &T2){
    BBSTree t1 = NULL,t2 = NULL;
    Split(T,e,t1,t2);//调用分裂函数，对分裂平衡二叉树进行操作
    T1 = t1; //（<=e）
    T2 = t2; //(>e)
}

/*构建一棵平衡二叉树*/
void CreatBBSTree(BBSTree &T){
    int num,i,e,taller = FALSE;
    printf("输入节点个数:");
    scanf("%d",&num);
    printf("请顺序输入结点值两个节点之间按空格隔开\n");
    for(i = 1 ; i <= num; i++){
        scanf("%d",&e); //输入每个节点
        InsertAVL(T,e,taller) ;//调用插入函数进行每个节点都插到空树上，完成建树
    }
    printf("构建成功\n");
}

/*凹入表形式演示平衡二叉树*/
void PrintBBSTree(BBSTree &T,int dep){
    int i;
    if(T->rchild) PrintBBSTree(T->rchild,dep+1); //对右子树递归
    for(i = 1; i <= dep; i++) /*凹凸表分隔距离*/
        printf("      ");
    printf("%d\n",T->data);  //打印数值
    if(T->lchild) PrintBBSTree(T->lchild,dep+1); //对左子树递归
}

/*查找算法*/
Status SearchBBSTree(BBSTree T,ElemType e){
    if(T==NULL) return FALSE; //空树，查找失败
    else if(e == T->data) return TRUE; //查找成功
    else if (e < T->data) return SearchBBSTree(T->lchild,e); //查找左子树
    else return SearchBBSTree(T->rchild,e); //查找右子树
}

/*采用后序遍历进行销毁树节点*/
void DestroyBBSTree(BBSTree &T){
    if(T){
        DestroyBBSTree(T->lchild);
        DestroyBBSTree(T->rchild);
        free(T);
    }
    T = NULL;
}
/*UI交互界面*/
void UI(int num){
        printf("\n********************************************************************************************\n");
        printf(" 基本操作：\n 当前对第 %d 棵平衡二叉树进行操作：1.创建 2.插入 3.查找 4.删除 5.演示 6.销毁 7.分裂 \n",num);
        printf(" 8.合并 9.清屏 0.退出\n");
        printf("********************************************************************************************\n");
}
/*UI交互界面提示功能实现，采用switch进行分数值询问响应*/
void StartUI(BBSTree T[]){
    int i,choice,taller,e,num,shorter;
    taller = FALSE;
    printf("\n********************************************************************************************\n");
    printf("**************************这里最多可存储 %d 棵平衡二叉树***********************************\n",N);
    printf("\n********************************************************************************************\n");

    while(1){
        printf("请输入对第几棵二叉树进行操作(按0退出)：");
        scanf("%d",&num);
        if(num<0 || num>N){
            printf("输入有误，请重新输入正确的指令（按0退出）\n");
            continue;
        }
        if(num==0){
            for(i=0;i<N;i++){
                if(T[i]) DestroyBBSTree(T[i]);
            }
            break;
        }
        UI(num);
        printf("输入你要进行的操作：");
        scanf("%d",&choice);
        num--;
        switch(choice){
            case 0:
                /*销毁所有树后退出程序*/
                for(i=0;i<N;i++){
                    if(T[i]) DestroyBBSTree(T[i]);
                }
                return ;
            case 1:
                if(T[num]==NULL){
                    printf("第 %d 棵当前为空树，可进行建树操作！\n",num+1);
                    CreatBBSTree(T[num]);
                }
                else{
                    char ch;
                    printf("第 %d 棵当前不是空树，是否继续进行建树操作？(Y/N)\n",num+1);
                    scanf("%c",&ch);
                    if(ch=='Y'){
                        DestroyBBSTree(T[num]);
                        CreatBBSTree(T[num]);
                    }
                    else printf("建树失败！\n");
                }
                break;
            case 2:
                taller = FALSE;
                printf("请输入要插入关键字的值:");
                scanf("%d",&e);
                InsertAVL(T[num],e,taller) ;
                break;
            case 3:
                printf("请输入要查找关键字的值:");
                scanf("%d",&e);
                if(SearchBBSTree(T[num],e)) printf("查找成功！\n");
                else printf("查找失败！\n");
                break;
            case 4:
                shorter = FALSE;
                printf("请输入要删除关键字的值：");
                scanf("%d",&e);
                if(SearchBBSTree(T[num],e)){
                    if(DeleteAVL(T[num],e,shorter)) printf("删除节点成功！\n");
                    else printf("删除节点失败！\n");
                }
                else printf("删除节点失败！因为第 %d 棵平衡二叉树不存在改节点\n",num+1);
                break;
            case 5:
                if(T[num]){
                    printf("\n第 %d 棵平衡二叉树演示\n",num+1);
                    printf("****************************************AVI*************************************************\n\n");
                    PrintBBSTree(T[num],2);
                    printf("\n********************************************************************************************\n");
                }
                else printf("第 %d 棵平衡二叉树是空树\n",num+1);
                break;
            case 6:
                printf("销毁第 %d 棵平衡二叉树成功\n",num+1);
                DestroyBBSTree(T[num]);
                break;
            case 7:
                /*查找是否存在可以存储分裂后的另一棵子树的位置*/
                if(T[num]){
                    int tag = FALSE;
                    for(i=0;i<N;i++){
                        if(T[i]==NULL && i!=num){
                            tag = TRUE;
                            break;
                        }
                    }
                    if(tag){
                        scanf("%d",&e);
                        SplitBBSTree(T[num],e,T[num],T[i]);
                        printf("分裂成功,分裂后的另一棵子树将存储于第 %d 棵平衡二叉树中\n",i+1);
                    }
                    else printf("分裂失败！由于当前没有空位置存储分裂后的另一棵子树\n");
                }
                else printf("分裂失败，当前第 %d 棵平衡二叉树是空树，无法进行分裂!\n",num+1);
                break;
            case 8:
                printf("请输入要和当前该树合并的另一棵树序号：");
                scanf("%d",&i);
                MergeBBSTree(T[num],T[i-1]);
                printf("合并成功！合并后的树将存储于第 %d 棵平衡二叉树中\n",num+1);
                break;
            case 9:
                system("cls");
                break;
            default : printf("输入指令有误，请重新输入正确的指令\n");break;
        }
        printf("\n\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n\n");
    }
}

int  main()
{
    BBSTree T[N];
    int i;
    for(i=0;i<N;i++) T[i] = NULL; //初始化每棵树为空树
    StartUI(T); //执行功能演示
    getchar();
    return 0;
}

#include<stdio.h>
#include<stdlib.h>

#define TRUE 1  //�ж����Ƿ������˻��߽�����
#define FALSE 0 //��ʾ���ĸ߶�û�иı�
#define LH +1 //��߸�
#define EH 0  //����һ����
#define RH -1 //�ұ߸�
#define N 10  //N���޶�ƽ��������Ŀ���
typedef int Status;
typedef int ElemType; // �������int���ͽ��в���

/*��ʽ�洢�ṹ*/
typedef struct BBSTNode{
    ElemType data;   //������
    int bf;          //ƽ������
    struct BBSTNode *lchild ,*rchild; //���Һ���ָ��
} BBSTNode,*BBSTree;

Status SearchBBSTree(BBSTree T,ElemType e);//���ҽڵ������

void R_Rotate(BBSTree &p);//����

void L_Rotate(BBSTree &p);//����

void LeftBalance(BBSTree &T);//������ƽ�����

void RightBalance(BBSTree &T);//������ƽ�����

Status InsertAVL(BBSTree &T,ElemType e,int &taller);//����ڵ�

void DELeftBalance(BBSTree &T);//ɾ����ƽ�����

void DERightBalance(BBSTree &T);//ɾ����ƽ�����

Status Delete(BBSTree &T,int &shorter);//ɾ������

void SDelete(BBSTree &T,BBSTree &q,BBSTree &s,int &shorter);//���Һ�̽ڵ����

Status DeleteAVL(BBSTree &T,ElemType e,int &shorter);//ɾ���ڵ����

void MergeBBSTree(BBSTree &T1,BBSTree &T2);//�ϲ�������

void SplitBBSTree(BBSTree T,ElemType e,BBSTree &T1,BBSTree &T2);//����������

void Split(BBSTree T,ElemType e,BBSTree &T1,BBSTree &T2); //�ݹ���Ѳ���

void PrintBBSTree(BBSTree &T,int dep); //�������ʾ

void DestroyBBSTree(BBSTree &T);// ����ƽ�������

/*��������*/
void R_Rotate(BBSTree &p){
    BBSTree lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}

/*��������*/
void L_Rotate(BBSTree &p){
    BBSTree rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}
/*������ƽ�����*/
void LeftBalance(BBSTree &T){
    BBSTree lc,rd;
    lc=T->lchild;
    switch(lc->bf){
        case LH: T->bf = lc->bf=EH;R_Rotate(T);break; //LL�ͣ�һ������
        case RH:                                      //LR�ͣ�һ��������һ������
            rd=lc->rchild;
            switch(rd->bf){
                /*�޸�ԭ��ƽ�����ӣ����ж��Ƿ���Ҫ����*/
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
/*������ƽ�����*/
void RightBalance(BBSTree &T){
    BBSTree rc,ld;
    rc=T->rchild;
    switch(rc->bf){
        case RH:T->bf= rc->bf=EH;L_Rotate(T);break;  //RR�ͣ�һ������
        case LH:                                     //RL�ͣ�һ��������һ������
            ld=rc->lchild;
            switch(ld->bf){
                case LH:T->bf=RH;rc->bf=EH;break;
                case EH:T->bf=rc->bf=EH;break;
                case RH:T->bf = EH;rc->bf=LH;break;
        }
        ld->bf=EH;
        R_Rotate(T->rchild);    //��T���к���Ϊ������
        L_Rotate(T);            //����
        break;
    }
}
/*����ڵ�*/
Status InsertAVL(BBSTree &T,ElemType e,int &taller)
{
    if(T==NULL){ /*�������½��ڵ�*/
        T= (BBSTree) malloc (sizeof(BBSTNode));
        T->data = e;
        T->lchild = T->rchild = NULL;
        T->bf = EH;
        taller = TRUE;   //�߶�����1
    }
    else{   /*�ǿ���*/
        if(e == T->data){ /*�Ѿ����ڸýڵ㣬�����в������*/
            taller = FALSE;
            return FALSE;
        }
        else if(e < T->data){ /*����ڵ�С�ڵ�ǰ�ڵ㣬���������ݹ��Ҳ���λ��*/
            if(!InsertAVL(T->lchild,e,taller)) return FALSE; // �Ҳ���������ʧ��
            if(taller) /*�Բ����߶ȱ仯���е���*/
                switch(T->bf){
                    /*��������۸߶ȱ仯ȡֵ��Ӱ��*/
                    case LH:LeftBalance(T);taller = FALSE;break; //����ˣ���ƽ�����
                    case EH:T->bf = LH;taller = TRUE;break;
                    case RH:T->bf = EH;taller = FALSE;break;
                }
        }
        else{ /*����ڵ���ڵ�ǰ�ڵ㣬���������ݹ��Ҳ���λ��*/
            if (!InsertAVL(T->rchild,e,taller)) return FALSE;
            if(taller) /*�Բ���ڵ��߶ȱ仯���з��������*/
                switch(T->bf){
                    case LH:T->bf = EH;taller = FALSE;break;
                    case EH:T->bf = RH;taller = TRUE;break;
                    case RH:RightBalance(T);taller = FALSE;break; //�ұ߸��ˣ���ƽ�����
                }
        }
    }
    return TRUE;
}
/*ɾ����ƽ�����*/
void DELeftBalance(BBSTree &T){
    BBSTree lc,rd;
    lc=T->lchild;
    switch(lc->bf){ /*��ɾ���ڵ������������ж��Ƿ���Ҫ����*/
        case LH:T->bf = EH;R_Rotate(T);break;
        case EH:T->bf = lc->bf= EH;R_Rotate(T);break; //��������
        case RH:
        rd=lc->rchild;
        switch(rd->bf){ /*ʧ�⣬�޸ĵ�ǰ�ڵ㼰������bfֵ�������к�������*/
            case LH:T->bf=RH;lc->bf=EH;break;
            case EH:T->bf=lc->bf=EH;break;
            case RH:T->bf=EH;lc->bf=LH;break;
        }
        rd->bf=EH;
        L_Rotate(T->lchild);  //ɾ��������LR�͵���
        R_Rotate(T);
    }
}
/*ɾ����ƽ�����*/
void DERightBalance(BBSTree &T){
    BBSTree rc,ld;
    rc=T->rchild;
    switch(rc->bf){/*������������ƽ������෴��˼������*/
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
/*Ѱ�Һ�̽ڵ㲢����ɾ���ڵ�λ��*/
void SDelete(BBSTree &T,BBSTree &q,BBSTree &s,int &shorter){
    if(s->rchild){/*ɾ���ڵ��������ǿգ��ݹ�Ѱ���ʺϵĺ�̽ڵ�*/
        SDelete(T,s,s->rchild,shorter);//�ݹ�
        if(shorter) /*�ж����ĸ߶��Ƿ�䰫��*/
            switch(s->bf){
                case EH:s->bf = LH;shorter = FALSE;break;
                case RH:s->bf = EH;shorter = TRUE;break;
                case LH:DELeftBalance(s);shorter = FALSE;break;
            }
        return;
    }
    /*��ǰɾ���ڵ�λ�õ���ֵ�޸�Ϊ��̽ڵ����ֵ*/
    T->data = s->data;
    if(q != T) q->rchild = s->lchild;
    else q->lchild = s->lchild;
    shorter = TRUE;
}
/*ɾ���ڵ�*/
Status Delete(BBSTree &T,int &shorter){
    BBSTree q;
    if(T->rchild==NULL){ /*������Ϊ�գ�ֱ��ɾ����ǰɾ���ڵ㣬�������������޸ĸ߶�*/
        q = T;
        T = T->lchild;
        free(q); //�ͷŽڵ�ռ�
        shorter = TRUE;
    }
    else if(T->lchild==NULL){ /*��������Ϊ�գ�����������������*/
        q = T;
        T= T->rchild;
        free(q);
        shorter = TRUE;
    }
    else{  /*�������������ǿ�*/
        SDelete(T,T,T->lchild,shorter);//�ݹ���Һ�̽ڵ����
        if(shorter) /*�ҵ���̽ڵ㲢�޸ĺ󣬻����жϸ߶ȱ仯�����ʵ�ƽ�����*/
            switch(T->bf){
                case EH:T->bf = RH;shorter = FALSE;break;
                case LH:T->bf = EH;shorter = TRUE;break;
                case RH:DERightBalance(T);shorter = FALSE;break;
            }
    }
    return TRUE;
}
/*����Ҫɾ���Ľڵ㣬ɾ���ڵ�*/
Status DeleteAVL(BBSTree &T,ElemType e,int &shorter){
    int sign = FALSE;
    if (T==NULL) return sign; //��Ϊ������ɾ��ʧ��
    else{ //�ҵ�Ҫɾ���Ľڵ㣬����Delete��ɾ������
        if(e == T->data){
            sign = Delete(T,shorter);
            return sign;
        }
        else if(e < T->data){ //ɾ���ڵ�ֵС�ڵ�ǰ�ڵ�ֵ
            sign = DeleteAVL(T->lchild,e,shorter);//��ݹ����ɾ���ڵ��Ƿ����
            if(shorter)/*����ƽ��*/
                switch(T->bf){
                    case EH:T->bf = RH;shorter = FALSE;break;
                    case LH:T->bf = EH;shorter = TRUE;break;
                    case RH:DERightBalance(T);shorter = TRUE;break;
                }
            return sign;
        }
        else{ /*�����������������������϶�����������*/
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
/*�ϲ�����ƽ�������*/
void MergeBBSTree(BBSTree &T1,BBSTree &T2){
    int taller = FALSE;
    if(T2==NULL) return;  //һ����Ϊ�գ�ֱ�ӷ��ؽ���
    MergeBBSTree(T1,T2->lchild); //��������T2�������ڵ�
    InsertAVL(T1,T2->data,taller); //�Ա��������Ľڵ�ֱ����T1��
    MergeBBSTree(T1,T2->rchild);//��������T2�������ڵ�
}
/*�ݹ���Ѳ���*/
void Split(BBSTree T,ElemType e,BBSTree &T1,BBSTree &T2){
    int taller = FALSE;
    if(T==NULL) return; //���ǿ�����ֱ�ӷ���
    Split(T->lchild,e,T1,T2);//������������e��������������ԭ��e����������С��e��
    if(T->data > e) InsertAVL(T2,T->data,taller); //�Է��ѳ����Ľڵ㣨>e�����뵽T2
    else InsertAVL(T1,T->data,taller); //��<e�����뵽T1
    Split(T->rchild,e,T1,T2);//����������
}
/*һ��ƽ�����������Ϊ����ƽ�������*/
void SplitBBSTree(BBSTree T,ElemType e,BBSTree &T1,BBSTree &T2){
    BBSTree t1 = NULL,t2 = NULL;
    Split(T,e,t1,t2);//���÷��Ѻ������Է���ƽ����������в���
    T1 = t1; //��<=e��
    T2 = t2; //(>e)
}

/*����һ��ƽ�������*/
void CreatBBSTree(BBSTree &T){
    int num,i,e,taller = FALSE;
    printf("����ڵ����:");
    scanf("%d",&num);
    printf("��˳��������ֵ�����ڵ�֮�䰴�ո����\n");
    for(i = 1 ; i <= num; i++){
        scanf("%d",&e); //����ÿ���ڵ�
        InsertAVL(T,e,taller) ;//���ò��뺯������ÿ���ڵ㶼�嵽�����ϣ���ɽ���
    }
    printf("�����ɹ�\n");
}

/*�������ʽ��ʾƽ�������*/
void PrintBBSTree(BBSTree &T,int dep){
    int i;
    if(T->rchild) PrintBBSTree(T->rchild,dep+1); //���������ݹ�
    for(i = 1; i <= dep; i++) /*��͹��ָ�����*/
        printf("      ");
    printf("%d\n",T->data);  //��ӡ��ֵ
    if(T->lchild) PrintBBSTree(T->lchild,dep+1); //���������ݹ�
}

/*�����㷨*/
Status SearchBBSTree(BBSTree T,ElemType e){
    if(T==NULL) return FALSE; //����������ʧ��
    else if(e == T->data) return TRUE; //���ҳɹ�
    else if (e < T->data) return SearchBBSTree(T->lchild,e); //����������
    else return SearchBBSTree(T->rchild,e); //����������
}

/*���ú�����������������ڵ�*/
void DestroyBBSTree(BBSTree &T){
    if(T){
        DestroyBBSTree(T->lchild);
        DestroyBBSTree(T->rchild);
        free(T);
    }
    T = NULL;
}
/*UI��������*/
void UI(int num){
        printf("\n********************************************************************************************\n");
        printf(" ����������\n ��ǰ�Ե� %d ��ƽ����������в�����1.���� 2.���� 3.���� 4.ɾ�� 5.��ʾ 6.���� 7.���� \n",num);
        printf(" 8.�ϲ� 9.���� 0.�˳�\n");
        printf("********************************************************************************************\n");
}
/*UI����������ʾ����ʵ�֣�����switch���з���ֵѯ����Ӧ*/
void StartUI(BBSTree T[]){
    int i,choice,taller,e,num,shorter;
    taller = FALSE;
    printf("\n********************************************************************************************\n");
    printf("**************************�������ɴ洢 %d ��ƽ�������***********************************\n",N);
    printf("\n********************************************************************************************\n");

    while(1){
        printf("������Եڼ��ö��������в���(��0�˳�)��");
        scanf("%d",&num);
        if(num<0 || num>N){
            printf("��������������������ȷ��ָ���0�˳���\n");
            continue;
        }
        if(num==0){
            for(i=0;i<N;i++){
                if(T[i]) DestroyBBSTree(T[i]);
            }
            break;
        }
        UI(num);
        printf("������Ҫ���еĲ�����");
        scanf("%d",&choice);
        num--;
        switch(choice){
            case 0:
                /*�������������˳�����*/
                for(i=0;i<N;i++){
                    if(T[i]) DestroyBBSTree(T[i]);
                }
                return ;
            case 1:
                if(T[num]==NULL){
                    printf("�� %d �õ�ǰΪ�������ɽ��н���������\n",num+1);
                    CreatBBSTree(T[num]);
                }
                else{
                    char ch;
                    printf("�� %d �õ�ǰ���ǿ������Ƿ�������н���������(Y/N)\n",num+1);
                    scanf("%c",&ch);
                    if(ch=='Y'){
                        DestroyBBSTree(T[num]);
                        CreatBBSTree(T[num]);
                    }
                    else printf("����ʧ�ܣ�\n");
                }
                break;
            case 2:
                taller = FALSE;
                printf("������Ҫ����ؼ��ֵ�ֵ:");
                scanf("%d",&e);
                InsertAVL(T[num],e,taller) ;
                break;
            case 3:
                printf("������Ҫ���ҹؼ��ֵ�ֵ:");
                scanf("%d",&e);
                if(SearchBBSTree(T[num],e)) printf("���ҳɹ���\n");
                else printf("����ʧ�ܣ�\n");
                break;
            case 4:
                shorter = FALSE;
                printf("������Ҫɾ���ؼ��ֵ�ֵ��");
                scanf("%d",&e);
                if(SearchBBSTree(T[num],e)){
                    if(DeleteAVL(T[num],e,shorter)) printf("ɾ���ڵ�ɹ���\n");
                    else printf("ɾ���ڵ�ʧ�ܣ�\n");
                }
                else printf("ɾ���ڵ�ʧ�ܣ���Ϊ�� %d ��ƽ������������ڸĽڵ�\n",num+1);
                break;
            case 5:
                if(T[num]){
                    printf("\n�� %d ��ƽ���������ʾ\n",num+1);
                    printf("****************************************AVI*************************************************\n\n");
                    PrintBBSTree(T[num],2);
                    printf("\n********************************************************************************************\n");
                }
                else printf("�� %d ��ƽ��������ǿ���\n",num+1);
                break;
            case 6:
                printf("���ٵ� %d ��ƽ��������ɹ�\n",num+1);
                DestroyBBSTree(T[num]);
                break;
            case 7:
                /*�����Ƿ���ڿ��Դ洢���Ѻ����һ��������λ��*/
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
                        printf("���ѳɹ�,���Ѻ����һ���������洢�ڵ� %d ��ƽ���������\n",i+1);
                    }
                    else printf("����ʧ�ܣ����ڵ�ǰû�п�λ�ô洢���Ѻ����һ������\n");
                }
                else printf("����ʧ�ܣ���ǰ�� %d ��ƽ��������ǿ������޷����з���!\n",num+1);
                break;
            case 8:
                printf("������Ҫ�͵�ǰ�����ϲ�����һ������ţ�");
                scanf("%d",&i);
                MergeBBSTree(T[num],T[i-1]);
                printf("�ϲ��ɹ����ϲ���������洢�ڵ� %d ��ƽ���������\n",num+1);
                break;
            case 9:
                system("cls");
                break;
            default : printf("����ָ������������������ȷ��ָ��\n");break;
        }
        printf("\n\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n\n");
    }
}

int  main()
{
    BBSTree T[N];
    int i;
    for(i=0;i<N;i++) T[i] = NULL; //��ʼ��ÿ����Ϊ����
    StartUI(T); //ִ�й�����ʾ
    getchar();
    return 0;
}

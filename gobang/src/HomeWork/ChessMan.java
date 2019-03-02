package HomeWork;

/*棋子类*/
public class ChessMan {
    private int color;  //black=1,white=0
    private boolean isplaced;
    public ChessMan(int color,boolean isplaced){
        this.color = color;
        this.isplaced = isplaced;
    }
    public boolean getIsplaced(){
        return isplaced;
    }
    public void setIsplaced(boolean choice){
        this.isplaced = choice;
    }
    public int getColor(){
        return color;
    }
    public void setColor(int color){ this.color = color; }
}

package map_info;

public class Point {
    public double x, y;
    public int index;

    public Point(){
        x = 0; 
        y = 0;
        index = -1;
    }

    public Point(double x_, double y_, int index_){
        x = x_;
        y = y_;
        index = index_;
    }
}

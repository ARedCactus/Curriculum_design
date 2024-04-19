package navigation;

import java.util.ArrayList;
import java.util.List;
import map_info.Line;

public class Nav {
    private ArrayList<Line> lines_;
    private ArrayList<Integer> road_data_ = new ArrayList<>();
    private ArrayList<Integer> point_AB_index_ = new ArrayList<>();
    private float[][] Mat;
    private int point_nums_;
    private float consumed_distance_ = -1;

    public Nav(ArrayList<Line> lines, int point_num){
        lines_ = lines;
        point_nums_ = point_num;
        Mat = new float[point_num][point_num];
    }

    public boolean setAB(int mouse_index){
        if(point_AB_index_.size() == 0){
            point_AB_index_.add(mouse_index);    
            return false;
        }
        consumed_distance_ = navigation(lines_, point_nums_, point_AB_index_.get(0), mouse_index).get(point_AB_index_.get(0));
        point_AB_index_.clear();
        return true;
    }

    public ArrayList<Integer> getRoadData(){
        return road_data_;
    }

    public float getDistance(){
        return consumed_distance_;
    }

    private List<Float> navigation(ArrayList<Line> lines, int point_num, int destination, int origination){
        float MaxF = Float.MAX_VALUE / 2;
        for(int i = 0; i < point_num; ++i)
            for(int j = 0; j < point_num; ++j)
                Mat[i][j] = MaxF;
        for(Line l : lines){
            Mat[l.a][l.b] = l.distance;
            Mat[l.b][l.a] = l.distance;
        }
        List<Float> distance = new ArrayList<>();
        ArrayList<Boolean> used = new ArrayList<>();
        ArrayList<Integer> road = new ArrayList<>();
        for(int i = 0; i < point_num; ++i){
            used.add(false);
            distance.add(MaxF);
            road.add(-1);
        }
        distance.set(origination, (float)0);

        for(int i = 0; i < point_num; ++i){
            int x = -1;
            for(int y = 0; y < point_num; ++y){
                if(!used.get(y) && (x == -1 || distance.get(y) < distance.get(x)))
                    x = y;
            }
            used.set(x, true);
            for(int y = 0; y < point_num; ++y){
                if(distance.get(y) > distance.get(x)+Mat[x][y]){
                    distance.set(y, distance.get(x)+Mat[x][y]);
                    road.set(y, x);
                }
            }
        }
        catchRoad(road, origination, destination);
        return distance;
    }

    private void catchRoad(ArrayList<Integer> road, int origination, int destination){
        road_data_.clear();
        int num = destination;
        int temp;
        while(num != origination){
            if(num == -1){
                road_data_.clear();
                break;
            }
            road_data_.add(num);
            temp = num;
            num = road.get(temp);
        }
        road_data_.add(origination);
    }

    public void clearRoad(){
        road_data_.clear();
        consumed_distance_ = -1;
    }
}

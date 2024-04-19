package map_info;

import java.util.ArrayList;
import ios.Read_yaml;
import navigation.Nav;

public class Scaling {
    private Point _00 = new Point(), slide_before_ = new Point(), split_ = new Point();
    private boolean find_state = false;
    private float scaling_rate = 1, scaling_spead;
    private int chosed_index, find_before_index_, each_L_split_;
    private int control_text_height = 0;

    private ArrayList<Point> P = new ArrayList<>();
    private ArrayList<Point> P_data = new ArrayList<>();
    private ArrayList<Point> P_border = new ArrayList<>();
    private ArrayList<Point> P_border_data = new ArrayList<>();
    private ArrayList<String> S = new ArrayList<>();
    private ArrayList<Line> L = new ArrayList<>();
    private ArrayList<ArrayList<Point>> F = new ArrayList<>(); 
    private ArrayList<Integer> config_int_;

    private DataIOS data_ios_ = new DataIOS();
    private Nav nav_;

    public Scaling() throws Exception{
        //读取 config 配置文件
        Read_yaml read_yaml = new Read_yaml();
        config_int_ = read_yaml.getConfigInt();
        scaling_spead = (float)read_yaml.getScalingSpead();
        split_.x = config_int_.get(0) / config_int_.get(4);
        split_.y = config_int_.get(1) / config_int_.get(5);
        each_L_split_ = config_int_.get(0) / config_int_.get(7);
        _00.x = -(config_int_.get(0)>>1);
        _00.y = -(config_int_.get(1)>>1);
        for(int i = 0; i < config_int_.get(4)*config_int_.get(5); ++i){
            ArrayList<Point> field = new ArrayList<>();
            F.add(field);
        }
        //读取地图数据 默认读取路径
        DataIOSRead(".\\data\\map_data\\Data.txt");
        reloadData();
        nav_ = new Nav(L, P.size());
    }

    //更改00坐标的值 用于鼠标滑动时
    public void set_00(int x, int y){
        _00.x += x;
        _00.y += y;
        // System.err.println(_00.x + " " + _00.y);
    }

    //更改00坐标的值 用于鼠标放缩时
    public void set_00(int x, int y, float spead){
        _00.x = x + spead * (_00.x - x);
        _00.y = y + spead * (_00.y - y);
        // System.err.println(_00.x + " " + _00.y);
    }

    //检测鼠标滑动
    public boolean mouseSliding(Point mouse){
        boolean bo_state = false;
        int x_ = (int)mouse.x, y_ = (int)mouse.y;
        int x = x_ - (int)slide_before_.x;
        int y = y_ - (int)slide_before_.y;
        if(x != 0 || y != 0){
            bo_state = true;
            for(Point p : P){
                p.x += x;
                p.y += y;
            }
            for(Point p : P_border){
                p.x += x;
                p.y += y;
            }
            set_00(x, y);  
        }
        slide_before_.x = mouse.x;
        slide_before_.y = mouse.y;
        return bo_state;
    }

    public boolean mouseScaling(Point mouse){
        int x = (int)mouse.x, y = (int)mouse.y;
        if(mouse.index == 0) return false;
        float spead = scaling_rate;
        boolean state = false;
        if(mouse.index == 1 && control_text_height > -config_int_.get(13)){
            spead = scaling_spead;
            --control_text_height;
            state = true;
        }
        else if(mouse.index == -1 && control_text_height < config_int_.get(14)){
            spead = 1 / scaling_spead;
            ++control_text_height;
            state = true;
        }
        if(state){
            for(Point p : P){
                p.x = x + spead * (p.x - x);
                p.y = y + spead * (p.y - y);
            }
            for(Point p : P_border){
                p.x = x + spead * (p.x - x);
                p.y = y + spead * (p.y - y);
            }
            scaling_rate *= spead;
            set_00(x, y, spead);
        }
        return true;
    }

    //返回虚拟点坐标 虚拟点坐标是参数点坐标在原始地图上的映射
    public Point virtualPoint(Point p){
        Point temp_p = new Point();
        temp_p.x = (p.x - _00.x)*(1/scaling_rate);
        temp_p.y = (p.y - _00.y)*(1/scaling_rate);
        temp_p.index = p.index;
        if(temp_p.x < 0) temp_p.x = 0;
        else if(temp_p.x >config_int_.get(0)) temp_p.x = config_int_.get(0);
        if(temp_p.y < 0) temp_p.y = 0;
        else if(temp_p.y > config_int_.get(1)) temp_p.y = config_int_.get(1);
        return temp_p;
    }

    public Point virtualPoint(int x, int y){
        Point temp_p = new Point();
        temp_p.x = (x - _00.x)*(1/scaling_rate);
        temp_p.y = (y - _00.y)*(1/scaling_rate);
        return temp_p;
    }

    //返回虚拟点所属区域集的编号
    //<参数point p 是经过_00坐标变换后的point>
    public int virtualField(Point p){
        int x = (int)(p.x / split_.x);   
        int y = (int)(p.y / split_.y);
        if(x < 0) x = 0;
        else if(x >= config_int_.get(4)) x = config_int_.get(4)-1;
        if(y < 0) y = 0;
        else if(y >= config_int_.get(5)) y = config_int_.get(5)-1;
        return config_int_.get(5)*y + x;
    }

    public int virtualField(int x, int y){
        Point p = virtualPoint(x, y);
        return virtualField(p);
    }

    public int virtualLField(Line l){
        double num = Math.min(P_data.get(l.a).x, P_data.get(l.b).x);
        double out = num / each_L_split_;
        if(out < 0) out = 0;
        else if(out > config_int_.get(5))
            out = config_int_.get(5);
        return (int)out;
    }

    public void setChosedIndex(int index){
        chosed_index = index;
    }

    public ArrayList<Point> getP(){
        return P;
    }

    public ArrayList<Point> getP_border(){
        return P_border;
    }

    public ArrayList<String> getPDataStr(){
        return S;
    }

    public ArrayList<Line> getL(){
        return L;
    }

    public void setSlideBefore(int x, int y){
        slide_before_.x = x;
        slide_before_.y = y;
    }

    private void addPointToFields(Point p){
        int field_index = virtualField(p);
        F.get(field_index).add(p);
    }

    public boolean whichPoint(Point mouse){
        Point virtual_mouse = virtualPoint(mouse);
        int field_index = virtualField(virtual_mouse);
        double x, y, x1, y1;
        for(Point p : F.get(field_index)){
            x = virtual_mouse.x - p.x;
            y = virtual_mouse.y - p.y;
            if(!find_state && x*x <= (int)(scaling_rate*config_int_.get(6))
                 && y*y <= (int)(scaling_rate*config_int_.get(6))){
                // System.err.println("find p index: "+p.index);
                find_before_index_ = p.index;
                find_state = true;
                setChosedIndex(p.index);
                return true;
            }
            else if(find_state){
                x1 = mouse.x - P.get(find_before_index_).x;
                y1 = mouse.y - P.get(find_before_index_).y;
                if(x1*x1 >= (int)(scaling_rate*config_int_.get(6))
                 || y1*y1 >= (int)(scaling_rate*config_int_.get(6))){
                    find_state = false;
                    return true;
                }
            }
        }
        return false;
    }

    public boolean getFindState(){
        return find_state;
    }

    public int getFindBeforeIndex(){
        return find_before_index_;
    }

    // public boolean twoPointToLine(){
    //     if(find_state)
    //         return read_line_.twoPointLine(chosed_index);
    //     return false;
    // }

    public boolean navAB(){
        if(find_state)
            return nav_.setAB(chosed_index);
        return false;
    }

    public ArrayList<Integer> getRoadData(){
        return nav_.getRoadData();
    }

    public void clearRoadData(){
        nav_.clearRoad();
    }

    public float getDistance(){
        return nav_.getDistance();
    }

    public int getScaleRate(){
        return (int)(10*scaling_rate);
    }

    public void DataIOSWrite(String file_path){
        data_ios_.write(P_border_data, P_data, S, L, file_path);
    }

    public void DataIOSRead(String file_path){
        data_ios_.read(P_border_data, P_data, S, L, file_path);
    }

    public void clearAllData(){
        for(ArrayList<Point> field : F)
            field.clear();
        P.clear();
        P_data.clear();
        P_border.clear();
        P_border_data.clear();
        S.clear();
        L.clear();
    }

    public void reloadData(){
        scaling_rate = 1;
        control_text_height = 0;
        _00.x = -(config_int_.get(0)>>1);
        _00.y = -(config_int_.get(1)>>1);
        if(!P_data.isEmpty()){
            for(Point p : P_data){
                addPointToFields(p);
                Point p_add = new Point(p.x+_00.x, p.y+_00.y, p.index);
                P.add(p_add);
            }
        }
        if(!P_border_data.isEmpty()){
            for(Point p : P_border_data){
                Point p_add = new Point(p.x+_00.x, p.y+_00.y, p.index);
                P_border.add(p_add);
            }
        }
        if(!L.isEmpty()){
            for(Line l : L){
                double x_dis = P_data.get(l.a).x - P_data.get(l.b).x;
                double y_dis = P_data.get(l.a).y - P_data.get(l.b).y;
                l.distance = (float)Math.sqrt(x_dis*x_dis + y_dis*y_dis);
            }
        }
    }
}

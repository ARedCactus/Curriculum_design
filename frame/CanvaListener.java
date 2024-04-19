package frame;

import java.awt.event.ActionListener;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelListener;
import java.util.ArrayList;

import javax.swing.JPanel;

import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;

import map_info.Point;
import map_info.Scaling;
import map_info.Line;

public class CanvaListener implements
ActionListener, MouseListener, MouseWheelListener, MouseMotionListener{
    private Frame_init frame_;
    private JPanel panel_;
    private ArrayList<Shape_> shape_list_;
    private Scaling scaling_;
    private ItemListener item_listener_;
    private Point mouse = new Point(); // press:index=1  release:index=0

    public CanvaListener() throws Exception{}

    public void setScaling(Scaling scaling){
        scaling_ = scaling;
    }

    public void setFrame(Frame_init frame){
        frame_ = frame;
    }

    public void setPanel(JPanel panel){
        panel_ = panel;
    }

    public void setShapeList(ArrayList<Shape_> shape_list){
        shape_list_ = shape_list;
    }

    public void setItemListener(ItemListener item_listener){
        item_listener_ = item_listener;
    }

    public void load(){
        ArrayList<Point> P_border = scaling_.getP_border();
        // for(Point p : P_border){
        //     Circle circle = new Circle(p, Color.BLACK, 4);
        //     shape_list_.add(circle);
        // }
        for(int i = 0; i < (P_border.size()>>1); ++i){
            L_Line line = new L_Line(P_border.get(2*i), P_border.get(2*i+1), Color.BLACK, scaling_.getScaleRate()/4);
            shape_list_.add(line);
        }
        ArrayList<Point> P = scaling_.getP();
        for(Line l : scaling_.getL()){
            L_Line line = new L_Line(P.get(l.a), P.get(l.b), Color.GREEN, scaling_.getScaleRate()/4+1);
            shape_list_.add(line);
        }
        for(Point p : P){
            Circle circle = new Circle(p, Color.CYAN, scaling_.getScaleRate()/2);
            shape_list_.add(circle);
        }
        ArrayList<Integer> road_data = scaling_.getRoadData();
        if(road_data.size() > 1){
            int behind_index = road_data.get(0);
            for(int i = 1; i < road_data.size(); i++){
                L_Line line = new L_Line(P.get(behind_index), P.get(road_data.get(i)), Color.RED, scaling_.getScaleRate()/4+1);
                shape_list_.add(line);
                behind_index = road_data.get(i);
            }
        }
        for(int x : road_data){
            Circle circle = new Circle(P.get(x), Color.ORANGE, scaling_.getScaleRate()/2);
            shape_list_.add(circle);
        }
        if(scaling_.getFindState()){
            Point find_before_point = scaling_.getP().get(scaling_.getFindBeforeIndex());
            Circle circle_finded = new Circle(find_before_point, Color.BLUE, scaling_.getScaleRate()/2+1);
            shape_list_.add(circle_finded);
        }
        int num = 0;
        for(String str : scaling_.getPDataStr()){
            Point p = P.get(num);
            Text text = new Text((int)p.x, (int)p.y, str, Color.BLACK,
                 new Font(Font.SANS_SERIF, Font.PLAIN, scaling_.getScaleRate()));
            shape_list_.add(text);
            num++;
        }
        if(scaling_.getDistance() != -1 && item_listener_.getIfShowDistance()){
            String distance = String.valueOf(scaling_.getDistance());
            distance = distance + " Km";
            Text text = new Text(frame_.getWidth()-25*distance.length(), 40, distance, Color.ORANGE,
                new Font(Font.SANS_SERIF, Font.PLAIN, 40));
            shape_list_.add(text);
        }
    }

    public void ament(){
        // System.err.println("ament");
        shape_list_.clear();
        load();
        mouse.index = 0;
        panel_.repaint();
    }

    public void actionPerformed(ActionEvent e){}

    public void mouseClicked(MouseEvent e){
        //用于添加新的 Line
        // if(scaling_.twoPointToLine()){
        //     ament();
        // }
        
        //用于Nav 设置AB点 并显示路径
        if(scaling_.navAB()){
            // road_data_ = scaling_.getRoadData();
            // distance_ = String.valueOf(scaling_.getDistance());
        }
    }

    public void mousePressed(MouseEvent e){
        mouse.index = 1;
        // System.out.println("press mouse_state:"+mouse.index);
    }

    public void mouseReleased(MouseEvent e){
        mouse.index = 0;
        // System.out.println("release mouse_state:"+mouse.index);
    }

    public void mouseEntered(MouseEvent e){}

    public void mouseExited(MouseEvent e){}

    public void mouseDragged(MouseEvent e){
        mouse.x = e.getX();
        mouse.y = e.getY();
        scaling_.mouseSliding(mouse);
        ament();
    }

    public void mouseMoved(MouseEvent e){
        mouse.x = e.getX();
        mouse.y = e.getY();
        if(scaling_.whichPoint(mouse)){
            shape_list_.clear();
            load();
            panel_.repaint();
        }
        
        scaling_.setSlideBefore(e.getX(), e.getY());
    }

    public void mouseWheelMoved(MouseWheelEvent e){
        mouse.index = e.getWheelRotation();
        mouse.x = e.getX();
        mouse.y = e.getY();
        scaling_.mouseScaling(mouse);
        ament();
    }
}

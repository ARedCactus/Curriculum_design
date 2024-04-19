package frame;

import java.awt.Graphics2D;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JPanel;

import java.awt.Graphics;
import java.awt.Dimension;
import java.awt.FlowLayout;
import javax.swing.JMenuBar;
import java.awt.Color;

import ios.Read_yaml;
import map_info.Scaling;

public class Frame_init extends JFrame{
    private ArrayList<JMenu> menu_list = new ArrayList<>();
    private ArrayList<JMenuItem> menu_item_list = new ArrayList<>();
    private ArrayList<Shape_> shape_list_ = new ArrayList<>();
    private Graphics2D graph_2d_;
    private CanvaListener canva_listener_ = new CanvaListener();
    private ItemListener item_listener = new ItemListener();
    private Scaling scaling_ = new Scaling();
    private JPanel jPanel_ = new JPanel(){
        public void paint(Graphics graph){
            graph_2d_ = (Graphics2D)graph;
            super.paint(graph_2d_);
            for(Shape_ x : shape_list_)
                x.draw(graph_2d_);    
    }};
    private Read_yaml config_ = new Read_yaml();
    
    public Frame_init() throws Exception{

    }

    public void showGUI() throws Exception{
        super.setTitle("nav_gui");
        super.setSize(config_.getConfigInt().get(2), config_.getConfigInt().get(3));
        super.setDefaultCloseOperation(3);
        super.setLocationRelativeTo(null);
        FlowLayout layout = new FlowLayout(FlowLayout.LEFT);
        super.setLayout(layout);
        super.setResizable(false);

        menu_list.add(new JMenu("文件"));
        menu_list.add(new JMenu("功能"));
        menu_list.add(new JMenu("开发者选项"));
        JMenuBar menu_bar = new JMenuBar();
        for(JMenu x : menu_list)
            menu_bar.add(x);
        this.setJMenuBar(menu_bar);

        menu_item_list.add(new JMenuItem("打开"));
        menu_item_list. add(new JMenuItem("保存"));
        menu_item_list.add(new JMenuItem("距离显示"));
        menu_item_list.add(new JMenuItem("清除路径"));
        menu_item_list.add(new JMenuItem("开发者选项"));

        for(JMenuItem x : menu_item_list)
            x.addActionListener(item_listener);

        for(int i = 0; i < 2; ++i)
            menu_list.get(0).add(menu_item_list.get(i));
        
        for(int i = 2; i < 4; ++i)
            menu_list.get(1).add(menu_item_list.get(i));
        
        menu_list.get(2).add(menu_item_list.get(4));
        
        jPanel_.setPreferredSize(
            new Dimension(config_.getConfigInt().get(2), config_.getConfigInt().get(3)-50));
        jPanel_.setBackground(Color.WHITE);
        this.add(jPanel_);
        
        item_listener.setScaling(scaling_);
        item_listener.setCanvaListener(canva_listener_);

        canva_listener_.setScaling(scaling_);
        canva_listener_.setFrame(this);
        canva_listener_.setPanel(jPanel_);
        canva_listener_.setShapeList(shape_list_);
        canva_listener_.setItemListener(item_listener);
        
        jPanel_.addMouseListener(canva_listener_);
        jPanel_.addMouseMotionListener(canva_listener_);
        jPanel_.addMouseWheelListener(canva_listener_);

        this.setVisible(true);
    }

    public void load(){
        canva_listener_.load();
    }
}

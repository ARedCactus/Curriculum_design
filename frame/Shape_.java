package frame;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.io.Serializable;

import map_info.Point;

import java.awt.BasicStroke;

abstract class Shape_ implements Serializable{
    Point p1 = new Point();
    Point p2 = new Point();
    Font font;
    Color color;
    float width;
    public abstract void draw(Graphics2D graph_2d_);
}

class Circle extends Shape_{
    public Circle(){
        p1.x = 100.0;
        p1.y = 100.0;
        p1.index = 1;
        p2.x = 200.0;
        p2.y = 200.0;
        p2.index = 2;
        color = Color.GREEN;
        width = 8;
    }
    public Circle(Point p1_, Color color_, float width_){
        p1.x = p1_.x;
        p1.y = p1_.y;
        color = color_;
        width = width_;
    }

    public void draw(Graphics2D graph_2d_){
        graph_2d_.setColor(color);
        // graph_2d_.setStroke(new BasicStroke(width));
        int width_2 = (int)Math.ceil(width/2);
        graph_2d_.fillOval((int)p1.x-width_2, (int)p1.y-width_2, (int)width, (int)width);
    }
}

class Text extends Shape_{
    private String str_;
    public Text(int x, int y, String str, Color color_, Font font_){
        p1.x = x;
        p1.y = y;
        str_ = str;
        this.color = color_;
        font = font_;
    } 

    public void draw(Graphics2D graph_2d_){
        graph_2d_.setColor(color);
        graph_2d_.setFont(font);
        graph_2d_.drawString(str_, (int)p1.x, (int)p1.y);
    }
}

class L_Line extends Shape_{
    public L_Line(Point p1_, Point p2_, Color color_, float width_){
        p1.x = p1_.x;
        p1.y = p1_.y;
        p2.x = p2_.x;
        p2.y = p2_.y;
        color = color_;
        width = width_;
    }

    public void draw(Graphics2D graph_2d_){
        graph_2d_.setColor(color);
        graph_2d_.setStroke(new BasicStroke(width));
        graph_2d_.drawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
    }
}


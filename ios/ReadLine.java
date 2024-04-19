package ios;

import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileReader;
import java.nio.charset.StandardCharsets;
import java.io.IOException;
import map_info.Line;
import java.io.BufferedWriter;
import java.io.FileWriter;

public class ReadLine {
    private ArrayList<Line> line_list_ = new ArrayList<>();
    private ArrayList<Integer> point_to_line_index_ = new ArrayList<>();
    private int line_nums = 0;
    
    public ReadLine(){
        laodLine(line_list_, "data\\map_data\\lines.txt");
    }

    private void laodLine(ArrayList<Line> line_list, String file_path){
        try (BufferedReader reader = new BufferedReader(new FileReader(file_path, StandardCharsets.UTF_8))) {  
            String one_line;  
            while ((one_line = reader.readLine()) != null) {  
                String[] parts = one_line.split(" ");  
                if (parts.length >= 2) {  
                    int a = Integer.parseInt(parts[0]);  
                    int b = Integer.parseInt(parts[1]); 
                    line_list.add(new Line(a, b, line_nums++));
                }  
            }  
        } catch (IOException e) {  
            e.printStackTrace();  
        }  
    }

    public ArrayList<Line> getLines(){
        return line_list_;
    }

    private void saveLinesIndex(ArrayList<Line> lines, String filePath) {  
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath, StandardCharsets.UTF_8))) {  
            for (Line l : lines) {  
                writer.write(l.a + " " + l.b + "\n");  
            }  
        } catch (IOException e) {
            e.printStackTrace();
        }  
    }

    public boolean twoPointLine(int mouse_index){
        if(point_to_line_index_.size() == 0){
            point_to_line_index_.add(mouse_index);
            return true;
        }
        else if(mouse_index != point_to_line_index_.get(0)){
            line_list_.add(new Line(mouse_index, point_to_line_index_.get(0), line_nums++));
            point_to_line_index_.clear();
            saveLinesIndex(line_list_, "data\\map_data\\lines.txt");
            return true;
        }
        return false;
    }
}

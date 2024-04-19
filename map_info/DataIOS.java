package map_info;

import java.io.BufferedWriter;  
import java.io.BufferedReader;
import java.io.FileWriter;  
import java.io.FileReader;
import java.io.IOException;  
import java.util.ArrayList;  
import java.nio.charset.StandardCharsets;

public class DataIOS {

    public void write(ArrayList<Point> P_border, ArrayList<Point> P, ArrayList<String> S, ArrayList<Line> L, String file_path){
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file_path, StandardCharsets.UTF_8))){
            writer.write("P_border_data:\n");
            for(Point p : P_border)
                writer.write((int)p.x + " " + (int)p.y + "\n");
            writer.write("P_data:\n");  
            for(int i = 0; i < P.size(); ++i){
                Point p = P.get(i);
                writer.write((int)p.x + " " + (int)p.y + " " + S.get(i) + "\n");
            }
            writer.write("line_data:\n");
            for(Line l : L)
                writer.write(l.a + " " + l.b + "\n");
            writer.flush(); // 确保所有数据都写入文件  
        }
        catch (IOException e) {  
            e.printStackTrace();  
        }
    }



    public void read(ArrayList<Point> P_border, ArrayList<Point> P, ArrayList<String> S, ArrayList<Line> L, String file_path){
        int read_state = 0;
        int P_nums = 0, P_border_nums = 0, L_nums = 0;
        try (BufferedReader reader = new BufferedReader(new FileReader(file_path, StandardCharsets.UTF_8))){
            String line; 
            while ((line = reader.readLine()) != null){
                if ("P_border_data:".equals(line)) read_state = 1;
                else if ("P_data:".equals(line)) read_state = 2;
                else if ("line_data:".equals(line)) read_state = 3;
                else{
                    String[] parts = line.split(" ");
                    if(read_state == 1){
                        if (parts.length == 2) {  
                            // double x = Double.parseDouble(parts[0]);  
                            // double y = Double.parseDouble(parts[1]);  
                            int x = Integer.parseInt(parts[0]);  
                            int y = Integer.parseInt(parts[1]);
                            P_border.add(new Point(x, y, P_border_nums++));  
                        }
                    }
                    else if(read_state == 2){
                        if (parts.length >= 3) {  
                            // double x = Double.parseDouble(parts[0]);  
                            // double y = Double.parseDouble(parts[1]);
                            int x = Integer.parseInt(parts[0]);  
                            int y = Integer.parseInt(parts[1]);  
                            String string = parts[2];  
                            P.add(new Point(x, y, P_nums++));  
                            S.add(string);
                        }
                    }
                    else{
                        if (parts.length == 2) {  
                            int a = Integer.parseInt(parts[0]);  
                            int b = Integer.parseInt(parts[1]); 
                            L.add(new Line(a, b, L_nums++));
                        }
                    }
                }
            }
        }
        catch (IOException e) {  
            e.printStackTrace();  
        }
    }
}

package ios;

import java.util.ArrayList;
import java.util.Random;
import java.io.BufferedReader;
import java.io.FileReader;
import java.nio.charset.StandardCharsets;
import java.io.IOException;  

import map_info.Point;

public class ReadPoint {
    private ArrayList<Point> P_data_ = new ArrayList<>();
    private ArrayList<Point> P_border_data_ = new ArrayList<>();
    private ArrayList<String> P_data_str_ = new ArrayList<>();
    private int p_nums_ = 0, p_border_nums = 0;

    public ReadPoint() throws Exception{
        loadPointsWithStrings(P_data_, P_data_str_, "data\\map_data\\points_with_chars.txt");
        loadOnlyPoints(P_border_data_, "data\\map_data\\points_border.txt");
    }

    public void randomPoints(int num){
        int index = 0;
        Random random = new Random();
        while(index++ < num){
            P_data_.add(new Point(random.nextDouble(1100), random.nextDouble(700), index));
            P_border_data_.add(new Point(random.nextDouble(1100), random.nextDouble(700), index));
        }
    }

    public ArrayList<Point> getPData(){
        return P_data_;
    }

    public ArrayList<String> getPDataStr(){
        return P_data_str_;
    }

    public ArrayList<Point> getP_border_Data(){
        return P_border_data_;
    }

    public int getPNums(){
        return p_nums_;
    }

    private void loadPointsWithStrings(ArrayList<Point> p_data, ArrayList<String> p_data_str, String filePath){  
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath, StandardCharsets.UTF_8))) {  
            String line;  
            while ((line = reader.readLine()) != null) {  
                String[] parts = line.split(" ");  
                if (parts.length >= 3) {  
                    int x = Integer.parseInt(parts[0]);  
                    int y = Integer.parseInt(parts[1]);  
                    String string = parts[2];  
                    p_data.add(new Point(x, y, p_nums_++));  
                    p_data_str.add(string);
                }  
            }  
        } catch (IOException e) {  
            e.printStackTrace();  
        }  
    }

    private void loadOnlyPoints(ArrayList<Point> points, String filename){
        try (BufferedReader reader = new BufferedReader(new FileReader(filename, StandardCharsets.UTF_8))) {  
            String line;  
            while ((line = reader.readLine()) != null) {  
                String[] parts = line.split(" ");  
                if (parts.length == 2) {  
                    int x = Integer.parseInt(parts[0]);  
                    int y = Integer.parseInt(parts[1]);  
                    points.add(new Point(x, y, p_border_nums++));  
                }  
            }  
        } catch (IOException e) {  
            e.printStackTrace();  
        }  
    }
}

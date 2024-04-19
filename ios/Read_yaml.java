package ios;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList; 
import java.util.List;  
import java.util.regex.Matcher;  
import java.util.regex.Pattern; 

public class Read_yaml {
    private ArrayList<Integer> config_int_ = new ArrayList<>();
    private ArrayList<String> config_str_ = new ArrayList<>();
    private double scaling_spead; 
    private static String filename_ = "data\\config.txt";

    public static List<Integer> extractIntegers(String input) {  
        List<Integer> numbers = new ArrayList<>();  
        Pattern pattern = Pattern.compile("\\d+");  
        Matcher matcher = pattern.matcher(input);  
        while (matcher.find()) {  
            numbers.add(Integer.parseInt(matcher.group()));  
        }  
        return numbers;  
    }  

    public static List<Double> extractNumbers(String input) {  
        List<Double> numbers = new ArrayList<>();  
        // 使用正则表达式匹配整数和小数  
        Pattern pattern = Pattern.compile("[-+]?\\d+(\\.\\d+)?");  
        Matcher matcher = pattern.matcher(input);  
        while (matcher.find()) {  
            numbers.add(Double.parseDouble(matcher.group()));  
        }  
        return numbers;  
    }   

    public static List<String> extractQuotedStrings(String input) {  
        List<String> quotedStrings = new ArrayList<>();  
        // 使用正则表达式匹配双引号包围的字符串  
        Pattern pattern = Pattern.compile("\"([^\"]*)\"");  
        Matcher matcher = pattern.matcher(input);  
        while (matcher.find()) {  
            // matcher.group(1) 会返回第一个捕获组的内容，即双引号之间的字符串  
            quotedStrings.add(matcher.group(1));  
        }  
        return quotedStrings;  
    }  

    public Read_yaml() throws Exception{
        FileInputStream ins = new FileInputStream(filename_);
        InputStreamReader reader = new InputStreamReader(ins, "utf-8");
        BufferedReader buffer = new BufferedReader(reader);
        String str;
        int change_state = 0, change_moment = 24;
        while((str = buffer.readLine()) != null){
            if(change_state < change_moment){
                List<Integer> arr = extractIntegers(str);
                if(arr.size() > 0)
                    config_int_.add(arr.get(0));
            }
            else if(change_state == change_moment){
                scaling_spead = extractNumbers(str).get(0);
            }
            else{
                List<String> arr = extractQuotedStrings(str);
                if(arr.size() > 0)
                    config_str_.add(arr.get(0));
            }
            change_state++;
        }
        buffer.close();
        // for(Integer x : config_int_)
        //     System.err.println(x);
        // System.err.println(scaling_spead);
        // for(String x : config_str_)
        //     System.err.println(x);
    }

    public ArrayList<Integer> getConfigInt(){
        return config_int_;
    }

    public double getScalingSpead(){
        return scaling_spead;
    }

    public ArrayList<String> getConfigStr(){
        return config_str_;
    }
}

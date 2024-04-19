package frame;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

import map_info.Scaling;
import java.io.File;
import java.time.LocalDate;  
import java.time.format.DateTimeFormatter;
import java.io.BufferedReader;  
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;  

public class ItemListener implements ActionListener{
    private Scaling scaling_;
    private CanvaListener canva_listener_;
    private boolean if_show_distance_ = true;

    public void setScaling(Scaling scaling){
        scaling_ = scaling;
    }

    public void setCanvaListener(CanvaListener canva_listener){
        canva_listener_ = canva_listener;
    }

    public void actionPerformed(ActionEvent e){
        String command = e.getActionCommand();
        
        if(command.equals("保存")){  
            LocalDate today = LocalDate.now(); 
            String dateString = today.format(DateTimeFormatter.ofPattern("yyyyMMdd"));  
            String fold_path = System.getProperty("user.dir")+"\\data\\new\\"+dateString;
            File folder = new File(fold_path);
            if(!folder.exists()){
                try{
                    folder.mkdirs();
                }catch(SecurityException se){
                    se.printStackTrace();
                }
            }
            JFileChooser file_chooser = new JFileChooser(fold_path);
            file_chooser.showSaveDialog(null);
            File file =file_chooser.getSelectedFile();
            if(file == null){
                scaling_.DataIOSWrite(fold_path+"\\Data.txt");
                JOptionPane.showMessageDialog(null, "没有填写文件名， 默认命名为Data.txt");
            }
            else{
                scaling_.DataIOSWrite(file.getAbsolutePath());
                JOptionPane.showMessageDialog(null, "文件已保存到"+file.getPath());
            }
        }
        else if(command.equals("打开")){
            JFileChooser fileChooser = new JFileChooser();
            fileChooser.setCurrentDirectory(new File(System.getProperty("user.dir")+"\\data"));  
            fileChooser.setDialogTitle("选择要加载的地图文件");  
            fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);  
            if(fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION){
                File selectedFile = fileChooser.getSelectedFile(); 
                scaling_.clearAllData();
                scaling_.DataIOSRead(selectedFile.getAbsolutePath());
                scaling_.reloadData();
                canva_listener_.ament();
                JOptionPane.showMessageDialog(null, "已加载"+selectedFile.getAbsolutePath());
            }
        }
        else if(command.equals("距离显示")){
            if_show_distance_ = !if_show_distance_;
            canva_listener_.ament();
        }

        else if(command.equals("清除路径")){
            scaling_.clearRoadData();
            canva_listener_.ament();
        }

        else if(command.equals("开发者选项")){
            JDialog popup = new JDialog();  
            popup.setTitle("开发者选项");  
            popup.setSize(600, 400);  
            popup.setModal(true);  
            popup.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);  
            try (BufferedReader reader = new BufferedReader(new FileReader(".\\data\\Developer.txt", StandardCharsets.UTF_8))){
                String text;
                String all_text = new String("");
                while ((text = reader.readLine()) != null){
                    all_text = all_text + text + "\n";
                }
                JTextArea textArea = new JTextArea(all_text);  
                textArea.setPreferredSize(new Dimension(400, 700));
                textArea.setEditable(false); // 如果不希望用户编辑文本，则设置为不可编辑  
                textArea.setLineWrap(true); // 设置自动换行  
                textArea.setWrapStyleWord(true); // 设置在单词边界处换行  
                JScrollPane scrollPane = new JScrollPane(textArea);  
  
            // 将JScrollPane添加到弹出窗口的内容面板中  
            popup.getContentPane().add(scrollPane, BorderLayout.CENTER);  
            popup.pack(); // 根据组件的首选大小调整弹出窗口的大小  
            }
            catch(IOException ioe) {  
                ioe.printStackTrace();  
            }
            popup.setLocationRelativeTo(null);  
            popup.setVisible(true);  
        }
    }  

    public boolean getIfShowDistance(){
        return if_show_distance_;
    }
}

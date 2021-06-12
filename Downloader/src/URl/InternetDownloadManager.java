package URl;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JButton;
import java.awt.BorderLayout;
import javax.swing.SwingConstants;
import java.awt.Window.Type;
import java.awt.Dialog.ModalExclusionType;
import javax.swing.JToggleButton;
import java.awt.Font;
import javax.swing.JTextField;
import javax.swing.JLabel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JProgressBar;

public class InternetDownloadManager {
	double percent;
	private JFrame frame;
	private JTextField textField;
	private JTextField textField_1;
	protected JLabel lblWow;
	protected JLabel lblWow_1;
	protected JLabel label;
	protected JLabel label_2;
	protected JProgressBar progressBar_1;
	private JTextField textField_2;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					InternetDownloadManager window = new InternetDownloadManager();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public InternetDownloadManager() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 526, 185);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		
		JButton btnDownload = new JButton("Download");
		btnDownload.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
				Download Z=new Download(textField.getText(),textField_1.getText(),0,0);
				Z.createfile();
				long size=Z.filesize;
				System.out.println(size);
				long number=Long.parseLong(textField_2.getText());
				long chunks=size/number;
				System.out.println(chunks);
				Download Z1[]=new Download[(int) number];
				for(int i=0;i<number;i++){
					Z1[i]=new Download(textField.getText(),textField_1.getText(),chunks*i,chunks*(i+1));
				}
				for(int i=0;i<number;i++){
					Z1[i].start();
				}
				
				/*boolean notalive=true;
				while(true) {
					for(int i=0;i<number;i++){
						//System.out.println(Z1[i].downloadedpercentage);
						percent+=Z1[i].downloadedpercentage;
						notalive = notalive&&!Z1[i].isAlive();
					}
					if(notalive==true) {
						progressBar_1.setValue((int)percent+(int)number);
						break;
					}
					notalive=true;
					System.out.println(percent);
					percent=0;
					
				}*/
				
				
			}
		});
		btnDownload.setFont(new Font("Sylfaen", Font.PLAIN, 18));
		btnDownload.setBounds(386, 10, 121, 95);
		frame.getContentPane().add(btnDownload);
		
		textField = new JTextField();
		textField.setFont(new Font("Tahoma", Font.PLAIN, 15));
		textField.setBounds(93, 10, 283, 25);
		frame.getContentPane().add(textField);
		textField.setColumns(10);
		
		JLabel lblNewLabel = new JLabel("URL:");
		lblNewLabel.setFont(new Font("Tahoma", Font.PLAIN, 15));
		lblNewLabel.setBounds(10, 10, 43, 25);
		frame.getContentPane().add(lblNewLabel);
		
		JLabel lblLocation = new JLabel("Location:");
		lblLocation.setFont(new Font("Tahoma", Font.PLAIN, 15));
		lblLocation.setBounds(10, 45, 61, 25);
		frame.getContentPane().add(lblLocation);
		
		textField_1 = new JTextField();
		textField_1.setFont(new Font("Tahoma", Font.PLAIN, 15));
		textField_1.setColumns(10);
		textField_1.setBounds(93, 45, 283, 25);
		frame.getContentPane().add(textField_1);
		
		progressBar_1 = new JProgressBar();
		progressBar_1.setBounds(10, 115, 497, 25);
		progressBar_1.setValue(0);
		frame.getContentPane().add(progressBar_1);
		
		JLabel lblNochunks = new JLabel("No.Chunks");
		lblNochunks.setFont(new Font("Tahoma", Font.PLAIN, 15));
		lblNochunks.setBounds(10, 80, 73, 25);
		frame.getContentPane().add(lblNochunks);
		
		textField_2 = new JTextField();
		textField_2.setFont(new Font("Tahoma", Font.PLAIN, 15));
		textField_2.setColumns(10);
		textField_2.setBounds(93, 80, 283, 25);
		frame.getContentPane().add(textField_2);
	}
}

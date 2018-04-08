package homework7;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class _14211145_吐尔荪江吾拉木_7_addBookUI extends JFrame implements ActionListener{
	private JButton submit = new JButton();
	private JButton Clear = new JButton();
	private JTextField myTextField1 = new JTextField(15);
	private JTextField myTextField2 = new JTextField(15);
	private JTextField myTextField3 = new JTextField(15);
	private JTextField myTextField4 = new JTextField(15);
	private JPanel panel = new JPanel();
	private JPanel panel1 = new JPanel();
	private JPanel panel2 = new JPanel();
	private JPanel panel3 = new JPanel();
	private JPanel panel4 = new JPanel();
	private JPanel panel5 = new JPanel();
	private _14211145_吐尔荪江吾拉木_7_Controller control;
	public _14211145_吐尔荪江吾拉木_7_addBookUI(_14211145_吐尔荪江吾拉木_7_Controller c){
		control=c;
		submit.addActionListener(this);
		Clear.addActionListener(this);
		final FlowLayout gridlayout = new FlowLayout();
		gridlayout.setAlignment(FlowLayout.LEFT);
		getContentPane().setLayout( gridlayout);
		panel.add(new JLabel("输入信息时类型为整型，范围<1，2，3，4>；价格为double型"));
		panel1.add(new JLabel("书号:"));
		panel1.add(myTextField1);
		panel2.add(new JLabel("书名:"));
		panel2.add(myTextField2);
		panel3.add(new JLabel("价格:"));
		panel3.add(myTextField3);
		panel4.add(new JLabel("类型:"));
		panel4.add(myTextField4);
		submit.setText("提交");
		panel5.add(submit);
		Clear.setText("重置");
		panel5.add(Clear);
		add(panel);
		add(panel1);
		add(panel2);
		add(panel3);
		add(panel4);
		add(panel5);
		setTitle("图书添加");
		setLocation(400,300);
		setSize(500,400);
		setVisible(true);	
	}
	public void actionPerformed(ActionEvent e) {
		if(e.getSource()==submit){
			boolean judge = myTextField1.getText().equals("")||myTextField2.getText().equals("")||
					myTextField3.getText().equals("")||myTextField4.getText().equals("");
			if(judge==false){
				control.addBook(myTextField1.getText(), myTextField2.getText(), Integer.parseInt(myTextField4.getText()),Double.parseDouble(myTextField3.getText()));
				JOptionPane.showMessageDialog(null, "添加图书成功", "提示", JOptionPane.ERROR_MESSAGE);
				myTextField1.setText(null);
				myTextField2.setText(null);
				myTextField3.setText(null);
				myTextField4.setText(null);
			}
			else
			{
				JOptionPane.showMessageDialog(null, "添加图书失败'\n'信息输入不完整", "提示", JOptionPane.ERROR_MESSAGE);
				myTextField1.setText(null);
				myTextField2.setText(null);
				myTextField3.setText(null);
				myTextField4.setText(null);
			}
			
		}
		if(e.getSource()==Clear){
			myTextField1.setText(null);
			myTextField2.setText(null);
			myTextField3.setText(null);
			myTextField4.setText(null);
		}
	}

}

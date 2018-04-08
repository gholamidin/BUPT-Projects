package homework7;

import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Iterator;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;

public class _14211145_吐尔荪江吾拉木_7_StrategiesUI extends JFrame implements ActionListener{
	/*private JMenu strategy1 = new JMenu("简单策略");
	private JMenu strategy2 = new JMenu("复杂策略");
	private JMenuItem item1 = new JMenuItem("修改");
	private JMenuItem item2 = new JMenuItem("查询");
	private JMenuItem item3 = new JMenuItem("增加");
	private JMenuItem item4 = new JMenuItem("删除");
	private JMenuItem item5 = new JMenuItem("修改");
	private JMenuItem item6 = new JMenuItem("查询");
	private JMenuItem item7 = new JMenuItem("增加");
	private JMenuItem item8 = new JMenuItem("删除");
	private JMenuBar bar = new JMenuBar();*/
	private JButton add = new JButton();
	private JButton delete = new JButton();
	private JButton change = new JButton();
	private JButton inquire = new JButton();
	private JPanel panel1 = new JPanel();
	private JPanel panel2 = new JPanel();
	private JPanel panel3 = new JPanel();
	private JPanel panel4 = new JPanel();
	private JTextField addmyTextField1 = new JTextField(15);
	private JTextField addmyTextField2 = new JTextField(15);
	private JTextField addmyTextField3 = new JTextField(15);
	private JTextField addmyTextField4 = new JTextField(15);
	private JTextField addmyTextField5 = new JTextField(15);
	private JTextField deletemyTextField1 = new JTextField(15);
	private JTextField changemyTextField1 = new JTextField(15);
	private JTextField changemyTextField2 = new JTextField(15);
	private JButton submit1 = new JButton();
	private JButton submit2 = new JButton();
	private JButton submit3 = new JButton();

	private JDialog window1;
	private JDialog window2;
	private JDialog window3;
	private JFrame tableFrame;
	private JScrollPane b;
	private _14211145_吐尔荪江吾拉木_7_Controller control;
	public _14211145_吐尔荪江吾拉木_7_StrategiesUI(_14211145_吐尔荪江吾拉木_7_Controller c){
		control=c;
		submit1.addActionListener(this);
		submit2.addActionListener(this);
		submit3.addActionListener(this);
		submit1.setText("提交");
		submit2.setText("提交");
		submit3.setText("提交");
		add.addActionListener(this);
		delete.addActionListener(this);
		change.addActionListener(this);
		inquire.addActionListener(this);
		add.setText("添加策略");
		delete.setText("删除策略");
		change.setText("更新策略");
		inquire.setText("查询策略");
		panel1.add(add);
		panel2.add(delete);
		panel3.add(change);
		panel4.add(inquire);
		add(panel1);
		add(panel2);
		add(panel3);
		add(panel4);
		final GridLayout gridlayout = new GridLayout();
		getContentPane().setLayout( gridlayout);
		setTitle("策略选项");
		setLocation(400,300);
		setSize(500,400);
		setVisible(true);
	}
	public void actionPerformed(ActionEvent e) {
		
		if(e.getSource()==add){addUI();}
		if(e.getSource()==delete){deleteUI();}
		if(e.getSource()==change){changeUI();}
		if(e.getSource()==inquire){inquireUI();}
		if(e.getSource()==submit1){
			boolean judge= addmyTextField1.getText().equals("")||addmyTextField2.getText().equals("")||
					addmyTextField3.getText().equals("")||addmyTextField4.getText().equals("")||addmyTextField5.getText().equals("");
			if(judge==false){
				control.addSimpleStrategy(addmyTextField1.getText(), Integer.parseInt(addmyTextField4.getText()), Double.parseDouble(addmyTextField5.getText())
						,addmyTextField2.getText(),addmyTextField3.getText());
				JOptionPane.showMessageDialog(null, "添加策略成功", "提示", JOptionPane.ERROR_MESSAGE);
				addmyTextField1.setText(null);
				addmyTextField2.setText(null);
				addmyTextField3.setText(null);
				addmyTextField4.setText(null);
				addmyTextField5.setText(null);
				
			}
			else{
				JOptionPane.showMessageDialog(null, "添加策略失败\n输入信息不完整", "提示", JOptionPane.ERROR_MESSAGE);
				addmyTextField1.setText(null);
				addmyTextField2.setText(null);
				addmyTextField3.setText(null);
				addmyTextField4.setText(null);
				addmyTextField5.setText(null);
				
			}
		}
		if(e.getSource()==submit2){
			boolean judge=true;
			int type=0;
			for(int i=0;i<control.getstrategycatalog().getStrategySpecification().size()&&judge;i++)
				if(deletemyTextField1.getText().equals(control.getstrategycatalog().getStrategySpecification().get(i).getIsbn())){
					judge=false;
					type=control.getstrategycatalog().getStrategySpecification().get(i).getBooktype();
					
				}
			if(judge==false){
				control.deleteStrategy(type);
				deletemyTextField1.setText(null);
				JOptionPane.showMessageDialog(null, "策略删除成功", "提示", JOptionPane.ERROR_MESSAGE);
			}
			else{
				JOptionPane.showMessageDialog(null, "删除策略失败\n输入信息不完整", "提示", JOptionPane.ERROR_MESSAGE);
				deletemyTextField1.setText(null);
			}
		}
		if(e.getSource()==submit3){
			boolean judge=true;
			for(int i=0;i<control.getstrategycatalog().getStrategySpecification().size()&&judge;i++)
				if(deletemyTextField1.getText().equals(control.getstrategycatalog().getStrategySpecification().get(i).getIsbn())){
					judge=false;
				}
			if(judge==false){
				control.updateStrategy(changemyTextField1.getText(),Double.parseDouble(changemyTextField2.getText()));
				JOptionPane.showMessageDialog(null, "策略更新成功", "提示", JOptionPane.ERROR_MESSAGE);
				changemyTextField1.setText(null);
				changemyTextField2.setText(null);
			}
			else{
				JOptionPane.showMessageDialog(null, "策略更新失败\n输入信息不完整", "提示", JOptionPane.ERROR_MESSAGE);
				changemyTextField1.setText(null);
				changemyTextField2.setText(null);
			}
		}
	}
	void addUI(){
		window1 = new JDialog();
		JPanel addpanel1 = new JPanel();
		JPanel addpanel2 = new JPanel();
		JPanel addpanel3 = new JPanel();
		JPanel addpanel4 = new JPanel();
		JPanel addpanel5 = new JPanel();
		JPanel addpanel6 = new JPanel();
		final FlowLayout gridlayout1 = new FlowLayout();
		gridlayout1.setAlignment(FlowLayout.LEFT);
		window1.setLayout(gridlayout1);
		addpanel1.add(new JLabel("                       策略编号:") );
		addpanel1.add(addmyTextField1);
		addpanel2.add(new JLabel("                       策略名称:") );
		addpanel2.add(addmyTextField2);
		addpanel3.add(new JLabel("                       策略类型:") );
		addpanel3.add(addmyTextField3);
		addpanel4.add(new JLabel("              适用类型:") );
		addpanel4.add(addmyTextField4);
		addpanel5.add(new JLabel("折扣百分比\\优惠额度:") );
		addpanel5.add(addmyTextField5);
		addpanel6.add(submit1);
		window1.add(addpanel1);
		window1.add(addpanel2);
		window1.add(addpanel3);
		window1.add(addpanel4);
		window1.add(addpanel5);
		window1.add(addpanel6);
		window1.setLocation(400,300);
		window1.setSize(400,400);
		window1.setVisible(true);
	}
	void deleteUI(){
		window2 = new JDialog();
		JPanel deletepanel1 = new JPanel();
		JPanel deletepanel2 = new JPanel();
		final FlowLayout gridlayout1 = new FlowLayout();
		gridlayout1.setAlignment(FlowLayout.LEFT);
		deletepanel1.add(new JLabel("策略编号:") );
		deletepanel1.add(deletemyTextField1);
		deletepanel2.add(submit2);
		window2.add(deletepanel1);
		window2.add(deletepanel2);
		window2.setLayout(gridlayout1);
		window2.setLocation(400,300);
		window2.setSize(300,400);
		window2.setVisible(true);
		
	}
	void changeUI(){
		window3 = new JDialog();
		JPanel changepanel1 = new JPanel();
		JPanel changepanel2 = new JPanel();
		JPanel changepanel3 = new JPanel();
		final FlowLayout gridlayout1 = new FlowLayout();
		gridlayout1.setAlignment(FlowLayout.LEFT);
		window3.setLayout(gridlayout1);
		changepanel1.add(new JLabel("                       策略编号:") );
		changepanel1.add(changemyTextField1);
		changepanel2.add(new JLabel("折扣百分比\\优惠额度:") );
		changepanel2.add(changemyTextField2);
		changepanel3.add(submit3);
		window3.add(changepanel1);
		window3.add(changepanel2);
		window3.add(changepanel3);
		window3.setLocation(400,300);
		window3.setSize(300,400);
		window3.setVisible(true);
	}
	void inquireUI(){
		tableFrame = new JFrame();
		Vector<Vector> v=new Vector<Vector>();
		Vector<String> v1=new Vector<String>();
		String[] head = {"策略编号" , "策略名称" , "策略类型",
				 "适用类型","折扣百分比\\优惠额度"};
		for(int i=0;i<head.length;i++){
			v1.add(head[i]);
		}
		java.util.Iterator<Integer> iter= control.getstrategycatalog().getStrategies().keySet().iterator();
		while(iter.hasNext()){
			int type = iter.next();
			for(int i=0;i<control.getstrategycatalog().getStrategySpecification().size();i++){
				if(type==control.getstrategycatalog().getStrategySpecification().get(i).getBooktype()){
					 Vector<String> infor=new Vector<String>();
					 infor.add(control.getstrategycatalog().getStrategySpecification().get(i).getIsbn());
					 infor.add(control.getstrategycatalog().getStrategySpecification().get(i).getName());
					 infor.add(control.getstrategycatalog().getStrategySpecification().get(i).getStrategytype());
					 infor.add(String.valueOf(control.getstrategycatalog().getStrategySpecification().get(i).getBooktype()));
					 if(type==1||type==3){
						 infor.add(String.valueOf(((_14211145_吐尔荪江吾拉木_7_PercentageStrategy)control.getstrategycatalog().getStrategies().get(type)).getDiscountPercentage()));
					 }
					 else if(type==2)
						 infor.add(String.valueOf(((_14211145_吐尔荪江吾拉木_7_FlatRateStrategy)control.getstrategycatalog().getStrategies().get(type)).getDiscountPerBook()));
					 else
						 infor.add(((_14211145_吐尔荪江吾拉木_7_CopositeStrategy)control.getstrategycatalog().getStrategies().get(type)).getInfor());
					 v.add(infor);
				}
			}
		}
		JTable table1 = new JTable(v,v1);
		b= new JScrollPane(table1);
		tableFrame.add(b);  
		tableFrame.pack();   
		tableFrame.setVisible(true);
	}
}

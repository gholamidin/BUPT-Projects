package homework7;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;

public class _14211145_吐尔荪江吾拉木_7_BuyUI extends JFrame implements ActionListener{

	private JButton submit = new JButton();
	private JButton search = new JButton();
 	private JTextField myTextField1 = new JTextField(15);
	private JTextField myTextField2 = new JTextField(15);
	private JPanel panel1 = new JPanel();
	private JPanel panel2 = new JPanel();
	private JPanel panel3 = new JPanel();
	private JScrollPane b;
	private _14211145_吐尔荪江吾拉木_7_ShoppingCarUI car;
	private Vector<Vector> v=new Vector<Vector>();
	private Vector<String> v1=new Vector<String>();
	private _14211145_吐尔荪江吾拉木_7_Controller control;
	
	
	public _14211145_吐尔荪江吾拉木_7_BuyUI(_14211145_吐尔荪江吾拉木_7_Controller c){
		control=c;
		submit.addActionListener(this);
		search.addActionListener(this);
		panel1.add(new JLabel("书号:"));
		panel1.add(myTextField1);
		panel2.add(new JLabel("购买数量:"));
		panel2.add(myTextField2);
		submit.setText("提交");
		panel3.add(submit);
		search.setText("查看购物车");
		panel3.add(search);
		final FlowLayout gridlayout = new FlowLayout();
		gridlayout.setAlignment(FlowLayout.LEFT);
		String[] head = {"title","isbn","type","price"};
		for(int i=0;i<head.length;i++){
			v1.add(head[i]);
		}
		init();
		JTable table1 = new JTable(v,v1);
		b= new JScrollPane(table1);
		
		add(b);  
		//pack();   
		getContentPane().setLayout( gridlayout);
		add(panel1);
		add(panel2);
		add(panel3);
		setTitle("图书购买");
		setLocation(400,150);
		setSize(500,600);
		setVisible(true);	
	}
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub 
		
		if(e.getSource()==submit){
			boolean x=true;
			int i=0;
			int type=0;
			for(i=0;i<control.getbookcatalog().getBooks().size()&&x;i++){
				if(control.getbookcatalog().getBooks().get(i).getIsbn().equals(myTextField1.getText())){
					x=false;
					type=control.getbookcatalog().getBooks().get(i).getType();
				}
			}
			if(x==false){
				control.buyBook(Integer.parseInt(myTextField2.getText()), control.getbookcatalog().getbook(myTextField1.getText()),
						control.getstrategycatalog().getstrategy(type));
				
				JOptionPane.showMessageDialog(null, "购买图书成功", "提示", JOptionPane.ERROR_MESSAGE);
				myTextField1.setText(null);
				myTextField2.setText(null);
			}
			else{
				myTextField1.setText(null);
				myTextField2.setText(null);
				JOptionPane.showMessageDialog(null, "购买图书失败\n不存在该书籍或者输入有误", "提示", JOptionPane.ERROR_MESSAGE);
			}

		}
		if(e.getSource()==search){
			//car.setVisible(false);
			car = new _14211145_吐尔荪江吾拉木_7_ShoppingCarUI(control.getSale());
			control.getSale().notifyObserver();
			
		}
		
	}
	public void init(){
		
		for(int i=0;i<control.getbookcatalog().getBooks().size();i++){
			Vector<String> infor=new Vector<String>();
			infor.add(control.getbookcatalog().getBooks().get(i).getTitle());
			infor.add(control.getbookcatalog().getBooks().get(i).getIsbn());
			infor.add(String.valueOf(control.getbookcatalog().getBooks().get(i).getType()));
			infor.add(String.valueOf(control.getbookcatalog().getBooks().get(i).getPrice()));
			v.add(infor);
		}
	}

}

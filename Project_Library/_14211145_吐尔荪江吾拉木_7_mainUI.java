package homework7;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class _14211145_吐尔荪江吾拉木_7_mainUI extends JFrame implements ActionListener{
	private JButton addbook = new JButton();
	private JButton buybook = new JButton();
	private JButton strategy = new JButton();
	private JPanel panel1 = new JPanel();
	private JPanel panel2 = new JPanel();
	private JPanel panel3 = new JPanel();
	// JPanel pane14= new JPanel();
	
	Icon icon=new ImageIcon("C:/Users/win10/Pictures/book.jpg");
	JLabel jl=new JLabel(icon);
	
	private _14211145_吐尔荪江吾拉木_7_Controller controller = new _14211145_吐尔荪江吾拉木_7_Controller();
	public _14211145_吐尔荪江吾拉木_7_mainUI(){
		
		addbook.addActionListener(this);
		buybook.addActionListener(this);
		strategy.addActionListener(this);
		buybook.setText("购买图书");
		addbook.setText("添加图书");
		strategy.setText("策略维护");
		
		panel1.add(addbook);
		panel2.add(buybook);
		panel3.add(strategy);
		//pane14.add(jl);
		jl.setBackground(Color.red);
		add(panel1);
		add(panel2);
		add(panel3);
		//add(pane14);
		
		final GridLayout gridlayout = new GridLayout();
		getContentPane().setLayout(gridlayout);
		setTitle("图书系统");
		setBackground(Color.red);
		setLocation(400,300);
		setSize(500,400);
		setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if(e.getSource()==addbook){
			_14211145_吐尔荪江吾拉木_7_addBookUI addBook = new _14211145_吐尔荪江吾拉木_7_addBookUI(controller);
			
		}
		if(e.getSource()==buybook){
			_14211145_吐尔荪江吾拉木_7_BuyUI buyBook = new _14211145_吐尔荪江吾拉木_7_BuyUI(controller);
			
		}
		if(e.getSource()==strategy){
			_14211145_吐尔荪江吾拉木_7_StrategiesUI S = new _14211145_吐尔荪江吾拉木_7_StrategiesUI(controller);
			
		}
		
	}

}

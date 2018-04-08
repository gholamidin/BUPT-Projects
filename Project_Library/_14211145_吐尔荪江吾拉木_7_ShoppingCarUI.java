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

public class _14211145_吐尔荪江吾拉木_7_ShoppingCarUI extends JFrame implements _14211145_吐尔荪江吾拉木_7_Observer,ActionListener{

	private JScrollPane b;
	private Vector<Vector> v=new Vector<Vector>();
	private Vector<String> v1=new Vector<String>();
	private JButton submit = new JButton();
	private JPanel panel1 = new JPanel();
	private JPanel panel2 = new JPanel();
	private _14211145_吐尔荪江吾拉木_7_Sale sale = new _14211145_吐尔荪江吾拉木_7_Sale();
	public _14211145_吐尔荪江吾拉木_7_ShoppingCarUI(_14211145_吐尔荪江吾拉木_7_Sale sale){
		//submit.addActionListener(this);
		this.sale=sale;
		this.sale.registerObserver(this);
		submit.addActionListener(this);
		panel1.add(new JLabel("结算价格:"+this.sale.getTotal()));
		submit.setText("提交");
		panel2.add(submit);
		final FlowLayout gridlayout = new FlowLayout();
		gridlayout.setAlignment(FlowLayout.LEFT);
		updata(sale);
		JTable table1 = new JTable(v,v1);
		b= new JScrollPane(table1);
		add(b);  
		pack();   
		getContentPane().setLayout( gridlayout);
		add(panel1);
		add(panel2);
		setTitle("购物车结算");
		setLocation(400,150);
		setSize(500,600);
		setVisible(true);	
	}
	public void updata(_14211145_吐尔荪江吾拉木_7_Sale temp) {
		// TODO Auto-generated method stub
		Vector<Vector> infor=new Vector<Vector>();
		Vector<String> infor2=new Vector<String>();
		String[] head = {"title","isbn","type","price","copies"};
		for(int i=0;i<head.length;i++){
			infor2.add(head[i]);
		}
		for(int i=0;i<temp.getItems().size();i++){
			Vector<String> infor1=new Vector<String>();
			infor1.add(temp.getItems().get(i).getProdSpec().getTitle());
			infor1.add(temp.getItems().get(i).getProdSpec().getIsbn());
			infor1.add(String.valueOf(temp.getItems().get(i).getProdSpec().getType()));
			infor1.add(String.valueOf(temp.getItems().get(i).getProdSpec().getPrice()));
			infor1.add(String.valueOf(temp.getItems().get(i).getCopies()));
			infor.add(infor1);
		}
		v=infor;
		v1=infor2;
			
	}
	public void Updata (_14211145_吐尔荪江吾拉木_7_Sale temp){
		setVisible(false);
		setVisible(true);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if(e.getSource()==submit){
			JOptionPane.showMessageDialog(null, "支付成功", "提示", JOptionPane.ERROR_MESSAGE);

		}
	}

}

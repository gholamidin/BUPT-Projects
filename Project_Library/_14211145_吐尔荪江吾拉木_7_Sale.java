package homework7;

import java.util.ArrayList;
import java.util.Iterator;

public class _14211145_吐尔荪江吾拉木_7_Sale implements _14211145_吐尔荪江吾拉木_7_Subject{
	private ArrayList<_14211145_吐尔荪江吾拉木_7_SaleLineitem> items=new ArrayList<_14211145_吐尔荪江吾拉木_7_SaleLineitem>();
	private double total=0;
	private _14211145_吐尔荪江吾拉木_7_Observer observer;
	public double getTotal(){
		total=0;
	    for(int i = 0;i < items.size(); i ++){
	    	System.out.println(items.get(i).getProdSpec().getType()+"类型的图书"
	    			+" "+"书名："+items.get(i).getProdSpec().getTitle()
	    			+" "+"购买量："+items.get(i).getCopies()+" "+"优惠后的价格："+
	    			items.get(i).getSubTotal());        
            total=total+items.get(i).getSubTotal();
        }
		return total;
	}
	public ArrayList<_14211145_吐尔荪江吾拉木_7_SaleLineitem> getItems() {
		return items;
	}
	public void setItems(ArrayList<_14211145_吐尔荪江吾拉木_7_SaleLineitem> items) {
		this.items = items;
	}
	public void fun(_14211145_吐尔荪江吾拉木_7_SaleLineitem a){
		items.add(a);	
	}
	@Override
	public void removeObserver(_14211145_吐尔荪江吾拉木_7_Observer temp) {
		// TODO Auto-generated method stub
		observer=temp=null;
	}
	@Override
	public void registerObserver(_14211145_吐尔荪江吾拉木_7_Observer temp) {
		// TODO Auto-generated method stub
		observer=temp;
		
	}
	@Override
	public void notifyObserver() {
		// TODO Auto-generated method stub
		observer.Updata(this);
	}
}

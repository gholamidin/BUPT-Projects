package homework7;

import java.util.ArrayList;

public class _14211145_�¶�ݥ������ľ_7_CopositeStrategy implements
		_14211145_�¶�ݥ������ľ_7_IPricingstrategy {
	private ArrayList<_14211145_�¶�ݥ������ľ_7_IPricingstrategy> strategies = new ArrayList<_14211145_�¶�ݥ������ľ_7_IPricingstrategy>();
	private String infor;
	public double getSubtotal(_14211145_�¶�ݥ������ľ_7_SaleLineitem temp) {
		// TODO Auto-generated method stub
		_14211145_�¶�ݥ������ľ_7_CompositeBestForCustomer s = new _14211145_�¶�ݥ������ľ_7_CompositeBestForCustomer(strategies);
		return s.getSubtotal(temp);
	}
	public void add(_14211145_�¶�ݥ������ľ_7_IPricingstrategy temp){
		strategies.add(temp);	
	}
	public String getInfor(){
		return infor;
	}
	public void setInfor(String infor){
		this.infor=infor;
		
	}

}

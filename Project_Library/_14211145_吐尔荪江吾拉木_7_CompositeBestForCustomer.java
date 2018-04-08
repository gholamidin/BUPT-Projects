package homework7;

import java.util.ArrayList;

public class _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_CompositeBestForCustomer extends _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_CopositeStrategy{
	private ArrayList<_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy> strategies = new ArrayList<_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy>();
	public _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_CompositeBestForCustomer(ArrayList<_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy> strategies){
		this.strategies=strategies;
	}
	public double getSubtotal(_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_SaleLineitem temp) {
		double min=strategies.get(0).getSubtotal(temp);
		for(int i=1;i<strategies.size();i++)
		{	
			System.out.println(min);
			System.out.println("n"+strategies.get(i).getSubtotal(temp));
			if(strategies.get(i).getSubtotal(temp)<min)
				min=strategies.get(i).getSubtotal(temp);
		}
		return min;
	}
}

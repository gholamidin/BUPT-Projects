package homework7;

public class _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_NoDiscountStrategy implements _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy{

	@Override
	public double getSubtotal(_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_SaleLineitem temp) {
		// TODO Auto-generated method stub
		return temp.getProdSpec().getPrice();
	}

}

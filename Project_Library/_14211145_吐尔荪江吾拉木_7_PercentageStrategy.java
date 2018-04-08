package homework7;

public class _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_PercentageStrategy implements _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy{

	private int discountPercentage;
	public _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_PercentageStrategy(int discountPercentage){
		this.discountPercentage=discountPercentage;
		
	}
	public double getSubtotal(_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_SaleLineitem temp) {
		// TODO Auto-generated method stub
		
		return (temp.getProdSpec().getPrice()*(100-discountPercentage))/100;
	}
	public int getDiscountPercentage() {
		return discountPercentage;
	}
	public void setDiscountPercentage(int discountPercentage) {
		this.discountPercentage = discountPercentage;
	}
}

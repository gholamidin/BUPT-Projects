package homework7;

public class _14211145_�¶�ݥ������ľ_7_NoDiscountStrategy implements _14211145_�¶�ݥ������ľ_7_IPricingstrategy{

	@Override
	public double getSubtotal(_14211145_�¶�ݥ������ľ_7_SaleLineitem temp) {
		// TODO Auto-generated method stub
		return temp.getProdSpec().getPrice();
	}

}

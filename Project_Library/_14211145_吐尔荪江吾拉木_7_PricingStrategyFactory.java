package homework7;

public class _14211145_吐尔荪江吾拉木_7_PricingStrategyFactory {
	private double subperbook=1;
	private int percent1=3;
	private int percent2=7;
	private _14211145_吐尔荪江吾拉木_7_PricingStrategyFactory instace;
	private _14211145_吐尔荪江吾拉木_7_StrategyCatalog Catalog;
	public _14211145_吐尔荪江吾拉木_7_PricingStrategyFactory getinstace(){
		return instace;
	}
	public _14211145_吐尔荪江吾拉木_7_IPricingstrategy getPricingStrategy(int type) 
			throws Exception{
		if(type==1){
			return new _14211145_吐尔荪江吾拉木_7_FlatRateStrategy(subperbook);
		}
		else if(type==2){
			return new _14211145_吐尔荪江吾拉木_7_PercentageStrategy(percent1);
		}
		else if(type==3){
			return new _14211145_吐尔荪江吾拉木_7_PercentageStrategy(percent2);
		}
		else if(type==4){
			return new _14211145_吐尔荪江吾拉木_7_NoDiscountStrategy();	
		}
		else
			throw new Exception("不存在这个策略！");
	}
	public void setCatalog(_14211145_吐尔荪江吾拉木_7_StrategyCatalog Catalog){
		this.Catalog=Catalog;
	}
	

}

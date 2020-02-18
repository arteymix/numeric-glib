namespace Libdfp
{
	[CCode (cname = "int", cprefix = "FE_DEC_", cheader_filename = "fenv.h")]
	public enum RoundingDirection
	{
		TONEAREST,
		TOWARDZERO,
		UPWARD,
		DOWNWARD,
		TONEARESTFROMZERO
	}
	[CCode (cname = "fe_dec_setround", cheader_filename = "fenv.h")]
	public RoundingDirection setround (RoundingDirection rounding_direction);
	[CCode (cname = "fe_dec_getround", cheader_filename = "fenv.h")]
	public RoundingDirection getround ();
}

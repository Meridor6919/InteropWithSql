using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;



namespace WPF
{
	public enum Events
	{
		LoginChange,
		PasswordChange,
		ButtonClick,
		last
	}
	public partial class LoginPage : Grid
	{
		public void DefaultEvent() {}
		public delegate void EventHandlerDelegate();
		public EventHandlerDelegate[] event_ptrs = new EventHandlerDelegate[((int)Events.last)];
		
		public LoginPage()
		{
			for (int i = 0; i < event_ptrs.Length; i++)
			{
				event_ptrs[i] = DefaultEvent;
			}
			InitializeComponent();
		}
		public void LoginChange(object sender, TextChangedEventArgs e) => event_ptrs[(int)Events.LoginChange]();
		public void PasswordChange(object sender, TextChangedEventArgs e) => event_ptrs[(int)Events.PasswordChange]();
		public void ButtonClick(object sender, RoutedEventArgs e) => event_ptrs[(int)Events.ButtonClick]();

		public ref Button GetButton()
		{
			return ref Button;
		}
		public ref TextBox GetLogin()
		{
			return ref Login;
		}
		public ref TextBox GetPassword()
		{
			return ref Password;
		}
	}
}


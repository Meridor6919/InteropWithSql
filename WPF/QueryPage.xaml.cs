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
using System.Windows.Shapes;

namespace WPF
{
	public enum QueryPageEvents
	{
		SQLQuery,
		ButtonClick,
		last
	}

	public partial class QueryPage : Grid
	{
		public void DefaultEvent() {}
		public delegate void EventHandlerDelegate();
		public EventHandlerDelegate[] event_ptrs = new EventHandlerDelegate[((int)QueryPageEvents.last)];
		public QueryPage()
		{
			for (int i = 0; i < event_ptrs.Length; i++)
			{
				event_ptrs[i] = DefaultEvent;
			}
			InitializeComponent();
		}
		public void SQLQueryChange(object sender, TextChangedEventArgs e) => event_ptrs[(int)QueryPageEvents.SQLQuery]();
		public void ButtonClick(object sender, RoutedEventArgs e) => event_ptrs[(int)QueryPageEvents.ButtonClick]();
		public ref Button GetButton()
		{
			return ref Button;
		}
		public ref TextBox GetSQLQuery()
		{
			return ref SQLQuery;
		}
		public ref DataGrid GetDataGrid()
		{
			return ref DataGrid;
		}
		public ref TextBlock GetError()
		{
			return ref Error;
		}
	}
}

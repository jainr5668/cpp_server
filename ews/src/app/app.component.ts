import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService } from '@utills/auth';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})
export class AppComponent {
  title = 'ews';
  isAuthenticated: boolean = false;
  menuSidebar = [
    {
      link_name: "Login",
      icon: "fa fa-fw fa-sign-in",
      link: "login",
      required_auth: false,
      sub_menu: []
    },
    {
      link_name: "Sign up",
      icon: "fa fa-fw fa-user-plus",
      link: "signup",
      required_auth: false,
      sub_menu: []
    },
    {
      link_name: "Todo",
      icon: "fa fa-fw fa-check-square",
      link: "todos",
      required_auth: true,
      sub_menu: []
    },
    {
      link_name: "Expense Manager",
      icon: "fa fa-fw fa-money",
      link: "expenseManager",
      required_auth: true,
      sub_menu: [
        {
          link_name: "Dashboard",
          link: "expenseManager/dashboard",
          icon: "fa fa-fw fa-tachometer",
          required_auth: true,
          sub_menu: []
        }
      ]
    },
  ];
  openSidebar: boolean = false;

  constructor(private authService: AuthService, private router: Router) {
    this.isAuthenticated = this.authService.isAuthenticated();
    AuthService.isAuthenticatedSubject.subscribe((isAuthenticated: boolean) => {
      this.isAuthenticated = isAuthenticated;
    });
  }

  showSubmenu(itemEl: HTMLElement) {
    itemEl.classList.toggle("showMenu");
  }

  logout(event) {
    this.authService.removeToken();
    this.router.navigate(['/']);
  }
}

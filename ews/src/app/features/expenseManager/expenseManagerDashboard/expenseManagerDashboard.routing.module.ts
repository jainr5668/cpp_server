import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ExpenseManagerDashboardComponent } from './expenseManagerDashboard.component';

const routes: Routes = [
  {
    path: '',
    component: ExpenseManagerDashboardComponent
  }
];
@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class ExpenseManagerDashboardRoutingModule { }

import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ExpenseManagerComponent } from './expenseManager.component';

const routes: Routes = [
  {
    path: '',
    component: ExpenseManagerComponent,
    children: [
    ]
  },
  {
    path: 'dashboard',
    loadChildren: () => import('./expenseManagerDashboard').then(m => m.ExpenseManagerDashboardModule)
  }
];
@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class ExpenseManagerRoutingModule { }

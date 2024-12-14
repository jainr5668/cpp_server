import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Observable } from 'rxjs';
import { StringIds, StringIdsType } from 'src/stringIds';
import { TranslateService } from '@ngx-translate/core';
import { ExpenseManagerDashboardModel } from './expenseManagerDashboard.model';

@Component({
  selector: 'feature-expenseManagerDashboard',
  templateUrl: './expenseManagerDashboard.component.html',
  styleUrls: ['./expenseManagerDashboard.component.css'],
})
export class ExpenseManagerDashboardComponent implements OnInit {
  @Input() public homepage: ExpenseManagerDashboardModel;

  @Output() clickListener = new EventEmitter();

  constructor(
    private translate: TranslateService
  ) {}

  ngOnInit(): void {
  }

  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }
}

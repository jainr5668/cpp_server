import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Observable } from 'rxjs';
import { StringIds, StringIdsType } from 'src/stringIds';
import { TranslateService } from '@ngx-translate/core';
import { ExpenseManagerModel } from './expenseManager.model';

@Component({
  selector: 'feature-expenseManager',
  templateUrl: './expenseManager.component.html',
  styleUrls: ['./expenseManager.component.css'],
})
export class ExpenseManagerComponent implements OnInit {
  @Input() public homepage: ExpenseManagerModel;

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

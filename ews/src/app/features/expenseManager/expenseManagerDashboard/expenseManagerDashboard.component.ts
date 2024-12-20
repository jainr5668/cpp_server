import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Observable } from 'rxjs';
import { StringIds, StringIdsType } from 'src/stringIds';
import { TranslateService } from '@ngx-translate/core';
import { ExpenseManagerDashboardModel } from './expenseManagerDashboard.model';
import { SummaryCardModel } from '@patterns/summaryCard';
import { ContentModel } from '@patterns/content';
import { CardModel } from '@patterns/card';

@Component({
  selector: 'feature-expenseManagerDashboard',
  templateUrl: './expenseManagerDashboard.component.html',
  styleUrls: ['./expenseManagerDashboard.component.css'],
})
export class ExpenseManagerDashboardComponent implements OnInit {
  @Input() public homepage: ExpenseManagerDashboardModel;

  @Output() clickListener = new EventEmitter();

  card:CardModel;
  constructor(
    private translate: TranslateService
  ) {}

  ngOnInit(): void {
    let summaryCard:SummaryCardModel = new SummaryCardModel();
    summaryCard.title = "Expense Manager";
    summaryCard.description = "Manage your expenses";
    summaryCard.colspan = 1;
    const content:ContentModel = new ContentModel();
    content.cols = 6;
    content.title = StringIds.cEMAIL;
    content.summaryCards = [summaryCard, summaryCard];
    this.card = new CardModel();
    this.card.title = StringIds.cEMAIL;
    this.card.contents = [content];
  }

  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }
}
